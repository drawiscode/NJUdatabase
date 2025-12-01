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

#include "lru_replacer.h"
#include "common/config.h"
#include "../common/error.h"
namespace njudb {

LRUReplacer::LRUReplacer() : cur_size_(0), max_size_(BUFFER_POOL_SIZE) {}

auto LRUReplacer::Victim(frame_id_t *frame_id) -> bool 
{
     //NJUDB_STUDENT_TODO(l1, t1); 
    std::lock_guard<std::mutex> guard(latch_);
    if (cur_size_ == 0) 
    {
        return false;
    }

    // 从尾部往前找第一个可被淘汰的元素
    for (auto rit = lru_list_.rbegin(); rit != lru_list_.rend(); ++rit) 
    {
        if (rit->second) 
        {  // 可被淘汰
        // 将 reverse_iterator 转为普通 iterator 指向该元素
        auto it = std::prev(rit.base());
        frame_id_t fid = it->first;
        // 从哈希表中移除
        lru_hash_.erase(fid);
        // 从链表中移除
        lru_list_.erase(it);
        // 更新计数
        --cur_size_;
        if (frame_id != nullptr) 
        {
            *frame_id = fid;
        }
        return true;
        }
    }

    // 没有找到可淘汰的帧
    return false;
}

void LRUReplacer::Pin(frame_id_t frame_id) 
{
    //NJUDB_STUDENT_TODO(l1, t1); 
    std::lock_guard<std::mutex> guard(latch_);
    auto it_find = lru_hash_.find(frame_id);
    if (it_find == lru_hash_.end()) 
    {
        // 不在 list 中，加入到头部，标记为不可淘汰
        lru_list_.push_front({frame_id, false});
        lru_hash_[frame_id] = lru_list_.begin();
        // 不可淘汰，不改变 cur_size_
    } 
    else 
    {
        // 在 list 中
        auto it = it_find->second;
        if (it->second) //unpin
        {
            --cur_size_;
            it->second = false;
        }
        // 节点移动到头部 最近使用
        lru_list_.splice(lru_list_.begin(), lru_list_, it);
        // 更新哈希中迭代器指向新的 begin()
        lru_hash_[frame_id] = lru_list_.begin();
    }
}

void LRUReplacer::Unpin(frame_id_t frame_id) 
{ 
    //NJUDB_STUDENT_TODO(l1, t1); 
    std::lock_guard<std::mutex> guard(latch_);
    auto it_find = lru_hash_.find(frame_id);
    if (it_find == lru_hash_.end()) 
    {
        // 不在 list 中，加入到头部，并标记为可淘汰
        lru_list_.push_front({frame_id, true});
        lru_hash_[frame_id] = lru_list_.begin();
        ++cur_size_;
    } 
    else 
    {
        auto it = it_find->second;
        if (!it->second) 
        {
            // 原先不可淘汰，改为可淘汰
            it->second = true;
            ++cur_size_;
        }
        // 无论是否从不可淘汰变为可淘汰，都把它视作最近使用 -> 移到前端
        //unpin ?
        //lru_list_.splice(lru_list_.begin(), lru_list_, it);
        //lru_hash_[frame_id] = lru_list_.begin();
    }
}

auto LRUReplacer::Size() -> size_t 
{ 
    //NJUDB_STUDENT_TODO(l1, t1); 
    std::lock_guard<std::mutex> guard(latch_);
    return cur_size_;
}

}  // namespace njudb
