/*------------------------------------------------------------------------------
 - Copyright (c) 2024. Websoft research group, Nanjing University.
 -
 - This program is free software: you can redistribute it and/or modify
 - it under the terms of the GNU General Public License as published by
 - the Free Software Foundation, either version 3 of the License, or
 - (at your option) any later version.
 -
 - This program is distributed in the hope that it will be useful,
 - but WITHOUT ANY WARRANTY; without even the implied warranty of
 - MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 - GNU General Public License for more details.
 -
 - You should have received a copy of the GNU General Public License
 - along with this program.  If not, see <https://www.gnu.org/licenses/>.
 -----------------------------------------------------------------------------*/

//
// Created by ziqi on 2024/7/17.
//
#include "buffer_pool_manager.h"
#include "page_guard.h"
#include "replacer/lru_replacer.h"
#include "replacer/lru_k_replacer.h"

#include "../../../common/error.h"

namespace njudb {

BufferPoolManager::BufferPoolManager(DiskManager *disk_manager, njudb::LogManager *log_manager, size_t replacer_lru_k)
    : disk_manager_(disk_manager), log_manager_(log_manager)
{
  if (REPLACER == "LRUReplacer") {
    replacer_ = std::make_unique<LRUReplacer>();
  } else if (REPLACER == "LRUKReplacer") {
    replacer_ = std::make_unique<LRUKReplacer>(replacer_lru_k);
  } else {
    NJUDB_FATAL("Unknown replacer: " + REPLACER);
  }
  // init free_list_
  for (frame_id_t i = 0; i < static_cast<int>(BUFFER_POOL_SIZE); i++) {
    free_list_.push_back(i);
  }
}

auto BufferPoolManager::FetchPage(file_id_t fid, page_id_t pid) -> Page * 
{ 
  //NJUDB_STUDENT_TODO(l1, t2); 
   std::lock_guard<std::mutex> guard(latch_);

  // 1) 如果已在缓冲池中 -> pin 并返回 Page*
  Frame *f=GetFrame(fid, pid);
  if (f != nullptr) 
  {
    // 找到对应的 frame_id（通过查表）
    auto it = page_frame_lookup_.find({fid, pid});
    NJUDB_ASSERT(it != page_frame_lookup_.end(), "page_frame_lookup_ inconsistent");
    frame_id_t frame_id = it->second;

    // 增加 pin_count 并通知 replacer 该帧不可被淘汰
    f->Pin();
    replacer_->Pin(frame_id);
    return f->GetPage();
  }

  // 2) 页面不在缓冲池，需获取可用 frame（free 或 victim）
  frame_id_t frame_id;
  try {
    frame_id = GetAvailableFrame();
  } catch (const NJUDBException_ &e) {
    // 没有可用 frame（全部被 pin），返回 nullptr 表示失败（调用者可处理）
    return nullptr;
  }

  Frame &frame = frames_[frame_id];

  // 3) 如果该 frame 原先存有页（非空），则其脏页需写回并移除旧映射
  //    注意：GetAvailableFrame 在返回 victim frame 时不会自动写回旧数据
  //    因此这里先处理旧页面的写回和映射删除
  Page *old_page = frame.GetPage();
  if (old_page->GetPageId() != INVALID_PAGE_ID) 
  {
    // 如果脏，写回
    if (frame.IsDirty()) 
    {
      disk_manager_->WritePage(old_page->GetFileId(), old_page->GetPageId(), old_page->GetData());
      frame.SetDirty(false);
    }
    // 移除旧映射
    page_frame_lookup_.erase({old_page->GetFileId(), old_page->GetPageId()});
  }

  // 4) 更新 frame 元信息（Reset -> 设置 fid/pid -> pin）
  //    UpdateFrame 会清除旧映射并设置 pin 状态、dirty 状态，并在 replacer 中标记为 pinned
  UpdateFrame(frame_id, fid, pid);

  // 5) 从磁盘读取页面内容到 frame 的 page 数据区
  disk_manager_->ReadPage(fid, pid, frames_[frame_id].GetPage()->GetData());

  // 已经设置为 pin（UpdateFrame 中处理），返回 page 指针
  return frames_[frame_id].GetPage();
}

auto BufferPoolManager::UnpinPage(file_id_t fid, page_id_t pid, bool is_dirty) -> bool 
{ 
  //NJUDB_STUDENT_TODO(l1, t2); 
  std::lock_guard<std::mutex> guard(latch_);

  Frame *frame = GetFrame(fid, pid);
  if (frame == nullptr) 
  {
    // 页面不在缓冲中
    return false;
  }

  // 不能对 pin_count == 0 的帧进行 unpin（上层逻辑错误）
  if (frame->GetPinCount() <= 0) 
  {
    return false;
  }

  // 标记脏
  if (is_dirty) 
  {
    frame->SetDirty(true);
  }

  // 递减 pin_count
  frame->Unpin();

  // 如果现在 pin_count == 0，则可以被 replacer 记录为可淘汰
  // 注意 replacer 的 Unpin 等价于“标记为 evictable 并作为一次访问”
  if (frame->GetPinCount() == 0) 
  {
    // 找出 frame_id
    //（GetFrame 已经返回了 frame 指针，通过 page_frame_lookup_ 找到对应 frame_id）
    // 找 key
    // 为效率这里用 linear search via page_frame_lookup_（map size 较小）；也可改为记录 frame_id 在 Frame 中
    // 但 page_frame_lookup_ 已经能反向映射
    // 查找对应映射：
    // (fid,pid) should exist in page_frame_lookup_
    auto it = page_frame_lookup_.find({fid, pid});
    if (it != page_frame_lookup_.end()) 
    {
      replacer_->Unpin(it->second);
    } 
    else 
    {
      // 若映射缺失则说明内部状态不一致，抛断言
      NJUDB_ASSERT(false, "UnpinPage: mapping not found");
    }
  }

  return true;
}

auto BufferPoolManager::DeletePage(file_id_t fid, page_id_t pid) -> bool 
{ 
  //NJUDB_STUDENT_TODO(l1, t2); 
  std::lock_guard<std::mutex> guard(latch_);

  Frame *frame = GetFrame(fid, pid);
  if (frame == nullptr) 
  {
    // 不在 buffer 中，视为已删除
    return true;
  }

  // 若正在被使用（pin_count>0），不能删除
  if (frame->GetPinCount() > 0) 
  {
    return false;
  }

  // 若是脏页，先写回磁盘
  Page *page = frame->GetPage();
  if (frame->IsDirty()) 
  {
    disk_manager_->WritePage(page->GetFileId(), page->GetPageId(), page->GetData());
    frame->SetDirty(false);
  }

  // 从映射中移除
  page_frame_lookup_.erase({fid, pid});

  // 重置 frame
  frame->Reset();

  // 把 frame 放回 free_list_
  frame_id_t idx = static_cast<frame_id_t>(frame - &frames_[0]);
  free_list_.push_back(idx); // get index; alternative below
  // 确保 replacer 中该 frame 不可见（将其标为 pinned，或让 replacer 管理移除）
  // 这里调用 Pin 确保 replacer 不会把这个 frame 当作 victim（也可提供接口移除）
  replacer_->Pin(idx);

  return true;
}

auto BufferPoolManager::DeleteAllPages(file_id_t fid) -> bool 
{ 
  //NJUDB_STUDENT_TODO(l1, t2); 
  std::lock_guard<std::mutex> guard(latch_);

  // 收集待删除的 keys，避免在遍历时修改 map
  std::vector<fid_pid_t> to_delete;
  to_delete.reserve(page_frame_lookup_.size());
  for (const auto &kv : page_frame_lookup_) 
  {
    if (kv.first.fid == fid) to_delete.push_back(kv.first);
  }

  for (const auto &fp : to_delete) 
  {
    Frame *frame = GetFrame(fp.fid, fp.pid);
    if (frame == nullptr) continue;
    if (frame->GetPinCount() > 0) 
    {
      return false; // 有正在被引用的页面，无法全部删除
    }
    // flush if dirty
    if (frame->IsDirty()) 
    {
      disk_manager_->WritePage(fp.fid, fp.pid, frame->GetPage()->GetData());
      frame->SetDirty(false);
    }
    // remove mapping and reset frame, push to free list
    page_frame_lookup_.erase(fp);
    frame->Reset();
    frame_id_t idx = static_cast<frame_id_t>(frame - &frames_[0]);
    free_list_.push_back(idx);
    replacer_->Pin(idx);
  }

  return true;
}

auto BufferPoolManager::FlushPage(file_id_t fid, page_id_t pid) -> bool 
{
   //NJUDB_STUDENT_TODO(l1, t2); 
  std::lock_guard<std::mutex> guard(latch_);

  Frame *frame = GetFrame(fid, pid);
  if (frame == nullptr) 
  {
    return false;
  }

  Page *page = frame->GetPage();
  if (frame->IsDirty()) 
  {
    disk_manager_->WritePage(page->GetFileId(), page->GetPageId(), page->GetData());
    frame->SetDirty(false);
  }
  return true;
}

auto BufferPoolManager::FlushAllPages(file_id_t fid) -> bool 
{ 
  //NJUDB_STUDENT_TODO(l1, t2); 
  std::lock_guard<std::mutex> guard(latch_);

  for (const auto &kv : page_frame_lookup_) 
  {
    const fid_pid_t &fp = kv.first;
    if (fp.fid != fid) continue;
    Frame &frame = frames_[kv.second];
    if (frame.IsDirty()) 
    {
      disk_manager_->WritePage(fp.fid, fp.pid, frame.GetPage()->GetData());
      frame.SetDirty(false);
    }
  }

  return true;
}

auto BufferPoolManager::GetAvailableFrame() -> frame_id_t 
{ 
  //NJUDB_STUDENT_TODO(l1, t2); 
  // free_list 优先
  if (!free_list_.empty()) 
  {
    frame_id_t fid = free_list_.front();
    free_list_.pop_front();
    return fid;
  }

  // 否则请求 replacer 淘汰一个 frame
  frame_id_t victim = INVALID_FRAME_ID;
  if (!replacer_->Victim(&victim)) 
  {
    // 没有可淘汰的 frame（全部被 pin）
    NJUDB_THROW(NJUDB_NO_FREE_FRAME, "No free frame");
  }

  return victim;
}

void BufferPoolManager::UpdateFrame(frame_id_t frame_id, file_id_t fid, page_id_t pid) 
{ 
  //NJUDB_STUDENT_TODO(l1, t2); 
   // caller holds latch_
  Frame &frame = frames_[frame_id];

  // 如果 frame 里有旧页且脏，需要先写回
  Page *old_page = frame.GetPage();
  if (old_page->GetPageId() != INVALID_PAGE_ID && frame.IsDirty()) 
  {
    disk_manager_->WritePage(old_page->GetFileId(), old_page->GetPageId(), old_page->GetData());
    frame.SetDirty(false);
  }

  // 移除旧映射（若存在）
  if (old_page->GetPageId() != INVALID_PAGE_ID) 
  {
    page_frame_lookup_.erase({old_page->GetFileId(), old_page->GetPageId()});
  }

  // 重置 frame（清空数据，pin_count=0, dirty=false）
  frame.Reset();

  // 设置新的 page 元信息
  Page *page = frame.GetPage();
  page->SetFilePageId(fid, pid);

  // pin the frame (we treat FetchPage as pinning it)
  frame.Pin();

  // 更新映射表
  page_frame_lookup_[{fid, pid}] = frame_id;

  // 标记 replacer 中该 frame 为 pinned（不可淘汰）
  replacer_->Pin(frame_id);
}

auto BufferPoolManager::GetFrame(file_id_t fid, page_id_t pid) -> Frame *
{
  const auto it = page_frame_lookup_.find({fid, pid});
  return it == page_frame_lookup_.end() ? nullptr : &frames_[it->second];
}

auto BufferPoolManager::FetchPageRead(file_id_t fid, page_id_t pid) -> ReadPageGuard
{
  Page *page = FetchPage(fid, pid);
  return {this, page, fid, pid};
}

auto BufferPoolManager::FetchPageWrite(file_id_t fid, page_id_t pid) -> WritePageGuard
{
  Page *page = FetchPage(fid, pid);
  return {this, page, fid, pid};
}

}  // namespace njudb
