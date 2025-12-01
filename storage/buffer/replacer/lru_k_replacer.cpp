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

#include "lru_k_replacer.h"
#include "common/config.h"
#include "../common/error.h"

namespace njudb {

void LRUKReplacer::LRUKNode::AddHistory(timestamp_t ts)
{
  history_.push_back(ts);
  if (history_.size() > k) 
  {
    history_.pop_front();
  }
}

auto LRUKReplacer::LRUKNode::GetBackwardKDistance(timestamp_t cur_ts) -> unsigned long long
{
  if (history_.size() < k) 
  {
    return std::numeric_limits<unsigned long long>::max();
  }
  return static_cast<unsigned long long>(cur_ts - history_.front());
}

auto LRUKReplacer::LRUKNode::IsEvictable() const -> bool 
{ 
    return is_evictable_; 
}

auto LRUKReplacer::LRUKNode::SetEvictable(bool set_evictable) -> void 
{ 
    is_evictable_ = set_evictable; 
}

LRUKReplacer::LRUKReplacer(size_t k) : max_size_(BUFFER_POOL_SIZE), k_(k) {}

auto LRUKReplacer::Victim(frame_id_t *frame_id) -> bool 
{ 
  //NJUDB_STUDENT_TODO(l1, f1);
  // lock 
  std::lock_guard<std::mutex> guard(latch_);

  if (cur_size_ == 0) 
  {
    return false;  // no evictable frames
  }

  // Choose the evictable frame with maximum backward-k distance
  frame_id_t best_fid = INVALID_FRAME_ID;
  unsigned long long best_dist = 0;

  for (auto &kv : node_store_) 
  {
    frame_id_t fid = kv.first;
    LRUKNode &node = kv.second;
    if (!node.IsEvictable()) continue;

    unsigned long long dist = node.GetBackwardKDistance(static_cast<timestamp_t>(cur_ts_));
    // select the frame with larger distance
    // If best_fid not set yet, pick current
    if (best_fid == INVALID_FRAME_ID || dist > best_dist ||(dist == best_dist && fid < best_fid)) 
    {
      best_dist = dist;
      best_fid = fid;
    }
  }

  if (best_fid == INVALID_FRAME_ID) 
  {
    return false;
  }

  // remove chosen node from store and update counters
  node_store_.erase(best_fid);
  --cur_size_;
  if (frame_id != nullptr) 
  {
    *frame_id = best_fid;
  }
  return true;  
}

void LRUKReplacer::Pin(frame_id_t frame_id) 
{ 
    //NJUDB_STUDENT_TODO(l1, f1); 
    std::lock_guard<std::mutex> guard(latch_);
    
    auto it = node_store_.find(frame_id);
    if (it == node_store_.end()) 
    {
        // insert new node
        auto res = node_store_.emplace(frame_id, LRUKNode(frame_id, k_));
        it = res.first;
    }
    LRUKNode &node = it->second;

    // record access with current timestamp, then increase cur_ts_
    node.AddHistory(static_cast<timestamp_t>(cur_ts_));
    ++cur_ts_;

    // mark as not evictable (pinned)
    if (node.IsEvictable()) 
    {
        node.SetEvictable(false);
        if (cur_size_ > 0) 
        {
        --cur_size_;
    } 
    else 
    {
      cur_size_ = 0;
    }
  }
}

void LRUKReplacer::Unpin(frame_id_t frame_id) 
{ 
    //NJUDB_STUDENT_TODO(l1, f1); 
    std::lock_guard<std::mutex> guard(latch_);
    
    auto it = node_store_.find(frame_id);
    if (it == node_store_.end()) 
    {
        auto res = node_store_.emplace(frame_id, LRUKNode(frame_id, k_));
        it = res.first;
    }
    LRUKNode &node = it->second;

    if (!node.IsEvictable()) 
    {
        node.SetEvictable(true);
        ++cur_size_;
    }
}

auto LRUKReplacer::Size() -> size_t 
{ 
    //NJUDB_STUDENT_TODO(l1, f1); 
    std::lock_guard<std::mutex> guard(latch_);
    return cur_size_;
}

}  // namespace njudb
