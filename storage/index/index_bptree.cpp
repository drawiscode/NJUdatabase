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
// Created by ziqi on 2024/7/28.
//

#include "index_bptree.h"
#include "../../../common/error.h"
#include "../buffer/page_guard.h"
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

#define TEST_BPTREE

namespace njudb {



static void DebugPrintLeaf(const BPTreeLeafPage *leaf_node, const RecordSchema *key_schema)
{
  return;
  // print all keys in the leaf node for debugging

  page_id_t leaf_page_id = leaf_node->GetPageId();
  printf("Leaf %d: ", leaf_page_id);
  for (int i = 0; i < leaf_node->GetSize(); i++) {
    Record current_key(key_schema, nullptr, leaf_node->KeyAt(i), INVALID_RID);
    printf("key[%d]: %s; ", i, current_key.GetValueAt(0)->ToString().c_str());
  }
  printf("\n");
}

static void DebugPrintInternal(const BPTreeInternalPage *internal_node, const RecordSchema *key_schema)
{
  return;
  // print all keys in the internal node for debugging
  page_id_t internal_page_id = internal_node->GetPageId();
  printf("Internal %d: ", internal_page_id);
  for (int i = 0; i < internal_node->GetSize(); i++) {
    Record current_key(key_schema, nullptr, internal_node->KeyAt(i), INVALID_RID);
    printf("key[%d]: %s, value: %d; ", i, current_key.GetValueAt(0)->ToString().c_str(), internal_node->ValueAt(i));
  }
  printf("\n");
}

// BPTreePage implementation
void BPTreePage::Init(idx_id_t index_id, page_id_t page_id, page_id_t parent_id, BPTreeNodeType node_type, int max_size)
{
  index_id_=index_id;
  page_id_=page_id;
  parent_page_id_=parent_id;
  node_type_=node_type;

  assert((max_size>=0)&&"BPTreePage::Init:error:max_size should be >=0");
  max_size_=static_cast<size_t>(max_size);
  //std::cout<<max_size_<<std::endl;
  size_=0;
}

auto BPTreePage::IsLeaf() const -> bool
{
  return node_type_==BPTreeNodeType::LEAF;
}

auto BPTreePage::IsRoot() const -> bool
{
  return parent_page_id_==INVALID_PAGE_ID;
}

auto BPTreePage::GetSize() const -> int
{
  assert(size_>=0);
  return static_cast<size_t>(size_);
}

auto BPTreePage::GetMaxSize() const -> int
{
  assert((max_size_>=0)&&"BPTreePage::GetMaxSize():error!max_size should be >=0");
  return static_cast<size_t>(max_size_);
}

void BPTreePage::SetSize(int size) 
{ 
  assert((size>=0)&&"BPTreePage::SetSize():size should be >=0");
  size_=size;
}

auto BPTreePage::GetPageId() const -> page_id_t
{
  return page_id_;
}

auto BPTreePage::GetParentPageId() const -> page_id_t
{
  return parent_page_id_;
}

void BPTreePage::SetParentPageId(page_id_t parent_page_id) 
{ 
  parent_page_id_=parent_page_id;  
}

auto BPTreePage::IsSafe(bool is_insert) const -> bool
{
  if(is_insert)//insert operation
  {
    if(size_==max_size_)
    {
      return false;
    }
    return true;
  }
  else//delete operation
  {
    if(size_<(max_size_/2))
    {
      return false;
    }
    return true;
  }
}

// BPTreeLeafPage implementation
void BPTreeLeafPage::Init(idx_id_t index_id, page_id_t page_id, page_id_t parent_id, int key_size, int max_size)
{
  BPTreePage::Init(index_id,page_id,parent_id,BPTreeNodeType::LEAF,max_size);
  next_page_id_=INVALID_PAGE_ID;
  key_size_=key_size;
}

auto BPTreeLeafPage::GetNextPageId() const -> page_id_t
{
  return next_page_id_;
}

void BPTreeLeafPage::SetNextPageId(page_id_t next_page_id) 
{ 
  next_page_id_=next_page_id;   
}

auto BPTreeLeafPage::KeyAt(int index) const -> const char *
{
  //NJUDB_ASSERT(index >= 0 && index < GetSize(), "Index out of bounds in KeyAt");
   NJUDB_ASSERT(index >= 0 && index < GetSize(), "Index out of bounds in KeyAt");
  return GetKeysArray()+static_cast<size_t>(index)*static_cast<size_t>(key_size_);
}

auto BPTreeLeafPage::ValueAt(int index) const -> RID
{
  NJUDB_ASSERT(index >= 0 && index < GetSize(), "Index out of bounds in ValueAt");
  return *(GetValuesArray()+index);
}

void BPTreeLeafPage::SetKeyAt(int index, const char *key) 
{ 
  memcpy((void*)(GetKeysArray()+static_cast<size_t>(index)*static_cast<size_t>(key_size_)),key,key_size_);
}

void BPTreeLeafPage::SetValueAt(int index, const RID &value) 
{ 
  //NJUDB_ASSERT(index >= 0 && index <= GetSize(), "Index out of bounds in SetValueAt");
  RID* target=GetValuesArray()+index;
  *target=value;
}

auto BPTreeLeafPage::KeyIndex(const Record &key, const RecordSchema *schema) const -> int
{
  //使用二分找到第一个大于等于目标键的位置
  //如果所有键都小于目标键，返回size_
  int sz = GetSize();
  int left=0;
  int right=sz-1;
  int ans=sz;
  while(left<=right)
  {
    int mid=(left+right)/2;
    Record current(schema,nullptr,KeyAt(mid),INVALID_RID);
    int cmp=Record::Compare(current,key);
    if(cmp>=0)//current>key
    {
      right=mid-1;
      ans=mid;
    }
    else//currnt<key 
    {
      left=mid+1;
    }
  }
  return ans;
}

auto BPTreeLeafPage::LowerBound(const Record &key, const RecordSchema *schema) const -> int
{
  // Find the first position where key <= keys[pos]
  // This is useful for >= queries
  int sz = GetSize();
  int left=0;
  int right=sz-1;
  int ans=sz;
  while(left<=right)
  {
    int mid=(left+right)/2;
    Record current(schema,nullptr,KeyAt(mid),INVALID_RID);
    int cmp=Record::Compare(current,key);
    if(cmp>=0)//current>key
    {
      right=mid-1;
      ans=mid;
    }
    else//currnt<key 
    {
      left=mid+1;
    }
  }
  return ans;
}

auto BPTreeLeafPage::UpperBound(const Record &key, const RecordSchema *schema) const -> int
{
  // Find the first position where key < keys[pos]
  // This is useful for < queries
  int sz = GetSize();
  int left=0;
  int right=sz-1;
  int ans=sz;
  while(left<=right)
  {
    int mid=(left+right)/2;
    Record current(schema,nullptr,KeyAt(mid),INVALID_RID);
    int cmp=Record::Compare(current,key);

    if(cmp>0)//current>key
    {
      ans=mid;
      right=mid-1;
    }
    else
    {
      left=mid+1;
    }
  }
  return ans;
}

auto BPTreeLeafPage::Lookup(const Record &key, const RecordSchema *schema) const -> std::vector<RID>
{
  int l=LowerBound(key,schema);
  int r=UpperBound(key,schema);
  std::vector<RID>results;
  for(int i=l;i<r;i++)
  {
    results.push_back(ValueAt(i));
  }
  return results;
}

auto BPTreeLeafPage::Insert(const Record &key, const RID &value, const RecordSchema *schema) -> int
{
  int size=GetSize();
  NJUDB_ASSERT(size<GetMaxSize(),"BPTreeLeafPage::Insert the leafnode is full");
  
  int insertPos=LowerBound(key,schema);
  //move value
  for(int i=size-1;i>=insertPos;i--)
  {
    //value[i+1]=value[i]
    SetValueAt(i+1,ValueAt(i));
    //key[i+1]=key[i]
    SetKeyAt(i+1,KeyAt(i));
  }
  //move key
  SetValueAt(insertPos,value);
  SetKeyAt(insertPos,key.GetData());
  //update size
  SetSize(size+1);
  return GetSize();
}

void BPTreeLeafPage::MoveHalfTo(BPTreeLeafPage *recipient) 
{ 
  int total=GetSize();
  int start=total/2;
  int moveCount=total-start;

  //
  char *keys=GetKeysArray()+static_cast<size_t>(start)*static_cast<size_t>(key_size_);
  RID *values=GetValuesArray()+start;
  recipient->CopyNFrom(keys,values,moveCount);

  SetSize(start);
}

void BPTreeLeafPage::CopyNFrom(const char *keys, const RID *values, int size) 
{ 
  int startPos=GetSize();
  NJUDB_ASSERT(startPos<GetMaxSize(),"BPTreeLeafPage::CopyNFrom() the leafnode is full");
  NJUDB_ASSERT(size>0,"BPTreeLeafPage::CopyFrom():the copy size is 0");

  NJUDB_ASSERT(size+startPos<=GetMaxSize(),"BPTreeLeafPage::CopyNFrom() the size is too large");
  //set values
  for(int i=startPos;i<startPos+size;i++)
  {
    SetValueAt(i,values[i-startPos]);
  }
  //set keys
  char *copyStart=GetKeysArray()+static_cast<size_t>(startPos)*static_cast<size_t>(key_size_);
  memcpy(copyStart,keys,static_cast<size_t>(size)*static_cast<size_t>(key_size_));
  
  SetSize(startPos+size);
}

auto BPTreeLeafPage::RemoveRecord(const Record &key, const RecordSchema *schema) -> int
{
  int index = LowerBound(key, schema);
  int size = GetSize();

  if (index == size) 
  {
    return size;
  }

  Record cur(schema, nullptr, KeyAt(index), INVALID_RID);
  if (Record::Compare(cur, key) != 0) 
  {
    return size;
  }

  // shift left
  for (int i = index + 1; i < size; i++) 
  {
    SetKeyAt(i - 1, KeyAt(i));
    SetValueAt(i - 1, ValueAt(i));
  }

  SetSize(size - 1);
  return GetSize();
}

void BPTreeLeafPage::MoveAllTo(BPTreeLeafPage *recipient) 
{ 
  //
  int moveCount=GetSize();
  char *keys=GetKeysArray();
  RID *values=GetValuesArray();
  recipient->CopyNFrom(keys,values,moveCount);
  //not sure
  //recipient->SetNextPageId(GetNextPageId());// not sure

  SetSize(0);
}

// BPTreeInternalPage implementation
void BPTreeInternalPage::Init(idx_id_t index_id, page_id_t page_id, page_id_t parent_id, int key_size, int max_size)
{
  BPTreePage::Init(index_id, page_id, parent_id, BPTreeNodeType::INTERNAL, max_size);
  key_size_ = key_size;
}

auto BPTreeInternalPage::KeyAt(int index) const -> const char *
{
  return GetKeysArray() + index * key_size_;
}

auto BPTreeInternalPage::GetKeySize() const -> int
{
  return key_size_;
}

auto BPTreeInternalPage::ValueAt(int index) const -> page_id_t
{
  return GetChildrenArray()[index];
}

void BPTreeInternalPage::SetKeyAt(int index, const char *key) 
{ 
   memcpy((void *)KeyAt(index), key, key_size_);
}

void BPTreeInternalPage::SetValueAt(int index, page_id_t value) 
{ 
  GetChildrenArray()[index] = value;
}

auto BPTreeInternalPage::Lookup(const Record &key, const RecordSchema *schema) const -> page_id_t
{
  int size = GetSize();
  for (int i = 1; i < size; i++) 
  {
    Record cur(schema, nullptr, KeyAt(i), INVALID_RID);
    if (Record::Compare(key, cur) < 0) 
    {
      return ValueAt(i - 1);
    }
  }
  return ValueAt(size - 1);
}

auto BPTreeInternalPage::LookupForLowerBound(const Record &key, const RecordSchema *schema) const -> page_id_t
{
  // For lower bound, we want to find the leftmost position where key could be inserted
  // This means finding the leftmost child that could contain keys >= key
  int size = GetSize();
  for (int i = 1; i < size; i++) 
  {
    Record cur(schema, nullptr, KeyAt(i), INVALID_RID);
    if (Record::Compare(key, cur) <= 0) 
    {
      return ValueAt(i - 1);
    }
  }
  return ValueAt(size - 1);
}

auto BPTreeInternalPage::LookupForUpperBound(const Record &key, const RecordSchema *schema) const -> page_id_t
{
  // For upper bound, we want to find the rightmost position where key could be inserted
  // This means finding the rightmost child that could contain keys <= key
  int size = GetSize();
  for (int i = 1; i < size; i++) 
  {
    Record cur(schema, nullptr, KeyAt(i), INVALID_RID);
    if (Record::Compare(key, cur) < 0) 
    {
      return ValueAt(i - 1);
    }
  }
  return ValueAt(size - 1);
}

void BPTreeInternalPage::PopulateNewRoot(page_id_t old_root_id, const Record &new_key, page_id_t new_page_id)
{
  SetValueAt(0, old_root_id);
  SetKeyAt(1, new_key.GetData());
  SetValueAt(1, new_page_id);
  SetSize(2);
}

auto BPTreeInternalPage::InsertNodeAfter(page_id_t old_value, const Record &new_key, page_id_t new_value) -> int
{
  int index = 0;
  while (index < GetSize() && ValueAt(index) != old_value) 
  {
    index++;
  }
  index++;

  for (int i = GetSize(); i > index; i--) 
  {
    SetKeyAt(i, KeyAt(i - 1));
    SetValueAt(i, ValueAt(i - 1));
  }

  SetKeyAt(index, new_key.GetData());
  SetValueAt(index, new_value);
  SetSize(GetSize() + 1);
  return GetSize();
}

void BPTreeInternalPage::MoveHalfTo(BPTreeInternalPage *recipient, BufferPoolManager *bpm)
{

  int total = GetSize();
  int mid = total / 2;   // mid 是 middle key 的 index

  // recipient 从 empty 开始
  recipient->SetSize(0);

  // 1. 拷贝右半部分（注意：keys 从 mid+1 开始）
  recipient->CopyNFrom(GetKeysArray() + (mid+1) * key_size_,GetChildrenArray() + mid ,total - mid, bpm);

  // 2. 原节点只保留左半部分（不包含 middle key）
  SetSize(mid);
}

void BPTreeInternalPage::CopyNFrom(const char *keys, const page_id_t *values, int size, BufferPoolManager *bpm)
{
  int start = GetSize();

  memcpy(GetKeysArray() + ((start+1) * key_size_), keys, (size-1) * key_size_);
  memcpy(GetChildrenArray() + start, values, size * sizeof(page_id_t));
  SetSize(start + size);

  for (int i = start; i < start + size; i++) 
  {
   { 
    auto guard = bpm->FetchPageWrite(index_id_, ValueAt(i));
    //auto child = reinterpret_cast<BPTreePage *>(guard.GetData());
    auto child = reinterpret_cast<BPTreePage *>(guard.GetMutableData());

   // std::cout<<"子节点id:"<<child->GetPageId()<<std::endl;
   // std::cout<<"正确的父节点id:"<<GetPageId()<<std::endl;

    child->SetParentPageId(GetPageId());
   }
  }
}

void BPTreeInternalPage::MoveAllTo(BPTreeInternalPage *recipient, const Record &middle_key, BufferPoolManager *bpm)
{
  // For internal nodes, we need to merge:
  // 1. The middle key from the parent (this becomes a key in the recipient)
  // 2. All keys and children from the source node
  //key copy

  recipient->SetKeyAt(recipient->GetSize(), middle_key.GetData());
  const char *keys=GetKeysArray()+key_size_;
  int keyCopySize=GetSize()-1;
  int recipientSize=recipient->GetSize();
  char *keyBegin=recipient->GetKeysArray()+((1+recipientSize)*(recipient->key_size_ ));
  memcpy(keyBegin,keys,keyCopySize*(recipient->key_size_));
  
  //child copy
  int childCopySize=GetSize();
  memcpy(recipient->GetChildrenArray()+recipient->GetSize(),GetChildrenArray(),childCopySize*sizeof(page_id_t));

  //
  int start=recipient->GetSize();
  recipient->SetSize(recipient->GetSize()+childCopySize);
  for (int i = start; i < recipient->GetSize(); i++) 
  {
   { 
    auto guard = bpm->FetchPageWrite(index_id_, recipient->ValueAt(i));
    auto child = reinterpret_cast<BPTreePage *>(guard.GetMutableData());
   // std::cout<<"子节点id:"<<child->GetPageId()<<std::endl;
   // std::cout<<"正确的父节点id:"<<GetPageId()<<std::endl;
    child->SetParentPageId(recipient->GetPageId());
   }
  }
  SetSize(0);
}

// BPTreeIndex implementation
BPTreeIndex::BPTreeIndex(DiskManager *disk_manager, BufferPoolManager *buffer_pool_manager, idx_id_t index_id,
    const RecordSchema *key_schema)
    : Index(disk_manager, buffer_pool_manager, IndexType::BPTREE, index_id, key_schema)
{

  // Initialize index header
  InitializeIndex();
}

void BPTreeIndex::InitializeIndex()
{
  // Get or create header page
  auto header_guard = buffer_pool_manager_->FetchPageWrite(index_id_, FILE_HEADER_PAGE_ID);
  if (!header_guard.IsValid()) {
    NJUDB_THROW(NJUDB_EXCEPTION_EMPTY, "Cannot fetch header page");
  }

  auto header = reinterpret_cast<BPTreeIndexHeader *>(header_guard.GetMutableData());

  // Check if already initialized
  if (header->page_num_ != 0) {
    return;
  }

  // first check if the header and the schema raw data can accomodate int the header file
  if (key_schema_->SerializeSize() + sizeof(BPTreeIndexHeader) > PAGE_SIZE) {
    NJUDB_THROW(NJUDB_INDEX_FAIL, "Key schema too large to fit in B+ tree header");
  }

  // Initialize header
  header->root_page_id_       = INVALID_PAGE_ID;
  header->first_free_page_id_ = INVALID_PAGE_ID;
  header->tree_height_        = 0;
  header->page_num_           = 1;  // Header page counts
  header->key_size_           = key_schema_->GetRecordLength();
  header->value_size_         = sizeof(RID);

  // Note: TEST_BPTREE mode is for testing your B+tree implementation.
  // you can only undef it after you have passed gtests and is ready to use it in executors.
#ifdef TEST_BPTREE
  std::cout << "TEST_BPTREE mode: using fixed max sizes" << std::endl;
  header->leaf_max_size_     = 4;
  header->internal_max_size_ = 4;
#else
  // Calculate max sizes based on page size

  size_t leaf_header_size     = sizeof(BPTreeLeafPage);
  size_t available_leaf_space = PAGE_SIZE - PAGE_HEADER_SIZE - leaf_header_size;
  header->leaf_max_size_      = available_leaf_space / (header->key_size_ + sizeof(RID));

  size_t internal_header_size     = sizeof(BPTreeInternalPage);
  size_t available_internal_space = PAGE_SIZE - PAGE_HEADER_SIZE - internal_header_size;
  header->internal_max_size_      = available_internal_space / (header->key_size_ + sizeof(page_id_t));

  // check if the max size of leaf and internal are valid
  if (static_cast<int>(header->leaf_max_size_) <= 0 || static_cast<int>(header->internal_max_size_) <= 0) {
    NJUDB_THROW(NJUDB_INDEX_FAIL, "Key too large for a B+ tree node to fit into a single page");
  }
#endif
}

auto BPTreeIndex::NewPage() -> page_id_t
{
  auto header_guard = buffer_pool_manager_->FetchPageWrite(index_id_, FILE_HEADER_PAGE_ID);
  auto header = reinterpret_cast<BPTreeIndexHeader *>(header_guard.GetMutableData());

  page_id_t new_page_id = static_cast<page_id_t>(header->page_num_);
  header->page_num_++;

  return new_page_id;
}

void BPTreeIndex::DeletePage(page_id_t page_id) { NJUDB_STUDENT_TODO(l4, t1); }

auto BPTreeIndex::FindLeafPage(const Record &key, bool leftMost) -> page_id_t
{
  auto header_guard = buffer_pool_manager_->FetchPageRead(index_id_, FILE_HEADER_PAGE_ID);
  auto header = reinterpret_cast<const BPTreeIndexHeader *>(header_guard.GetData());

  page_id_t page_id = header->root_page_id_;
  if (page_id == INVALID_PAGE_ID) 
  {
    return INVALID_PAGE_ID;
  }

  while (true) 
  {
    page_id_t next_page_id;
    {
      auto page_guard = buffer_pool_manager_->FetchPageRead(index_id_, page_id);
      auto page = reinterpret_cast<const BPTreePage *>(page_guard.GetData());

      if (page->IsLeaf()) 
      {
        return page_id;
      }

      auto internal = reinterpret_cast<const BPTreeInternalPage *>(page);
      next_page_id = leftMost ? internal->ValueAt(0)
                              : internal->Lookup(key, key_schema_);
    } // ✅ page_guard 在这里析构，自动 Unpin

    page_id = next_page_id;
  }
}

auto BPTreeIndex::FindLeafPageForRange(const Record &key, bool isLowerBound) -> page_id_t
{
  auto header_guard =buffer_pool_manager_->FetchPageRead(index_id_, FILE_HEADER_PAGE_ID);
  auto header =reinterpret_cast<const BPTreeIndexHeader *>(header_guard.GetData());

  page_id_t page_id = header->root_page_id_;
  if (page_id == INVALID_PAGE_ID) 
  {
    return INVALID_PAGE_ID;
  }

  while (true) 
  {
    page_id_t next_page_id;
    {
      auto page_guard =buffer_pool_manager_->FetchPageRead(index_id_, page_id);
      auto page =reinterpret_cast<const BPTreePage *>(page_guard.GetData());

      if (page->IsLeaf()) 
      {
        return page_id;
      }

      auto internal =reinterpret_cast<const BPTreeInternalPage *>(page);

      if (isLowerBound)
      {
        // lower_bound: 找第一个 key >= target
        int i = 1;
        int n = internal->GetSize();  // key 数

        for (; i < n; i++) 
        {
          // 构造 Record 才能 Compare
          Record internal_key(key_schema_, nullptr, internal->KeyAt(i), INVALID_RID);

          if (Record::Compare(key, internal_key) <= 0) 
          {
            break;
          }
        }

        next_page_id = internal->ValueAt(i-1);
      } 
      else 
      {
        // 点查找 / upper_bound 语义
        next_page_id = internal->Lookup(key, key_schema_);
      }
    } // page_guard 在这里析构，自动 Unpin

    page_id = next_page_id;
  }
}

void BPTreeIndex::StartNewTree(const Record &key, const RID &value) 
{ 
  //分配 root page id
  page_id_t root_page_id = NewPage();

  // Fetch root page
  auto root_guard = buffer_pool_manager_->FetchPageWrite(index_id_, root_page_id);
  auto leaf = reinterpret_cast<BPTreeLeafPage *>(root_guard.GetMutableData());

  // 初始化 leaf
  auto header_guard = buffer_pool_manager_->FetchPageRead(index_id_, FILE_HEADER_PAGE_ID);
  auto header = reinterpret_cast<const BPTreeIndexHeader *>(header_guard.GetData());

  leaf->Init(index_id_, root_page_id, INVALID_PAGE_ID,
             header->key_size_, header->leaf_max_size_);

  //插入第一条记录
  leaf->Insert(key, value, key_schema_);

  // 更新 header
  auto header_guard2 = buffer_pool_manager_->FetchPageWrite(index_id_, FILE_HEADER_PAGE_ID);
  auto header2 = reinterpret_cast<BPTreeIndexHeader *>(header_guard2.GetMutableData());

  header2->root_page_id_ = root_page_id;
  header2->tree_height_ = 1;
  header2->num_entries_ = 1; 
}

auto BPTreeIndex::InsertIntoLeaf(const Record &key, const RID &value) -> bool 
{ 
  page_id_t leaf_page_id = FindLeafPage(key);
  auto leaf_guard = buffer_pool_manager_->FetchPageWrite(index_id_, leaf_page_id);
  auto leaf = reinterpret_cast<BPTreeLeafPage *>(leaf_guard.GetMutableData());

  // 1. 如果有空间，直接插
  if (leaf->GetSize() < leaf->GetMaxSize()) 
  {
    leaf->Insert(key, value, key_schema_);

    auto header_guard = buffer_pool_manager_->FetchPageWrite(index_id_, FILE_HEADER_PAGE_ID);
    auto header = reinterpret_cast<BPTreeIndexHeader *>(header_guard.GetMutableData());
    header->num_entries_++;

    return true;
  }

  // 2. 否则，需要 split
  page_id_t new_leaf_page_id = NewPage();
  auto new_leaf_guard = buffer_pool_manager_->FetchPageWrite(index_id_, new_leaf_page_id);
  auto new_leaf = reinterpret_cast<BPTreeLeafPage *>(new_leaf_guard.GetMutableData());

  auto header_guard = buffer_pool_manager_->FetchPageRead(index_id_, FILE_HEADER_PAGE_ID);
  auto header = reinterpret_cast<const BPTreeIndexHeader *>(header_guard.GetData());

  new_leaf->Init(index_id_, new_leaf_page_id, leaf->GetParentPageId(),header->key_size_, header->leaf_max_size_);

  // 4. 移动一半到新 leaf
  leaf->MoveHalfTo(new_leaf);


   // 4. 判断 key 应该插哪一边
  if (Record::Compare(key, Record(key_schema_, nullptr, new_leaf->KeyAt(0), INVALID_RID)) < 0)
  {
    leaf->Insert(key, value, key_schema_);
  }
  else
  {
    new_leaf->Insert(key, value, key_schema_);
  }

  //debug
  //std::cout<<"After leaf split :"<<std::endl;
  DebugPrintLeaf(leaf, key_schema_);
  DebugPrintLeaf(new_leaf, key_schema_);

  // 5. 维护链表
  new_leaf->SetNextPageId(leaf->GetNextPageId());
  leaf->SetNextPageId(new_leaf_page_id);

  // 6. 把新 leaf 的第一个 key 插入 parent
  Record middle_key(key_schema_, nullptr, new_leaf->KeyAt(0), INVALID_RID);
  InsertIntoParent(leaf_page_id, middle_key, new_leaf_page_id);

  auto header_guard2 = buffer_pool_manager_->FetchPageWrite(index_id_, FILE_HEADER_PAGE_ID);
  auto header2 = reinterpret_cast<BPTreeIndexHeader *>(header_guard2.GetMutableData());
  header2->num_entries_++;

  return true;
}

void BPTreeIndex::InsertIntoParent(page_id_t old_node_id,const Record &key,page_id_t new_node_id)
{
  page_id_t parent_page_id;

  /* ----------  只读 old_node，用完立刻释放 ---------- */
  {
    auto old_guard = buffer_pool_manager_->FetchPageRead(index_id_, old_node_id);
    auto old_node = reinterpret_cast<const BPTreePage *>(old_guard.GetData());

    if (old_node->IsRoot())
    {
      // root 情况直接处理，不能继续向上
      InsertIntoNewRoot(old_node_id, key, new_node_id);
      return;
    }

    parent_page_id = old_node->GetParentPageId();
  } 

  /* ----------  处理 parent（可能插入 / 可能分裂） ---------- */
  page_id_t new_parent_page_id = INVALID_PAGE_ID;
  Record middle_key = key;  // 先占位，真正用时再覆盖

  {
    auto parent_guard = buffer_pool_manager_->FetchPageWrite(index_id_, parent_page_id);
    auto parent = reinterpret_cast<BPTreeInternalPage *>(parent_guard.GetMutableData());

    /* ----------  父节点未满：直接插 ---------- */
    if (parent->GetSize() < parent->GetMaxSize())
    {
      parent->InsertNodeAfter(old_node_id, key, new_node_id);

      //std::cout << "父节点未满，直接插 ===parent insert ===" << std::endl;
      DebugPrintInternal(parent, key_schema_);

      return; //  parent_guard 析构
    }

    // 先插再 split（非常重要）
    parent->InsertNodeAfter(old_node_id, key, new_node_id);

    // 创建新 internal page
    new_parent_page_id = NewPage();
    auto new_parent_guard =
        buffer_pool_manager_->FetchPageWrite(index_id_, new_parent_page_id);
    auto new_parent =
        reinterpret_cast<BPTreeInternalPage *>(new_parent_guard.GetMutableData());

    // 读 header
    auto header_guard =buffer_pool_manager_->FetchPageRead(index_id_, FILE_HEADER_PAGE_ID);
    auto header =reinterpret_cast<const BPTreeIndexHeader *>(header_guard.GetData());

    new_parent->Init(index_id_,
                     new_parent_page_id,
                     parent->GetParentPageId(),
                     header->key_size_,
                     header->internal_max_size_);

    // 取 middle key（在 split 前）
    int mid = parent->GetSize() / 2;
    middle_key =Record(key_schema_, nullptr, parent->KeyAt(mid), INVALID_RID);

    // split
    parent->MoveHalfTo(new_parent, buffer_pool_manager_);

    DebugPrintInternal(parent, key_schema_);
    DebugPrintInternal(new_parent, key_schema_);

  } 

  InsertIntoParent(parent_page_id, middle_key, new_parent_page_id);
}


/*void BPTreeIndex::InsertIntoParent(page_id_t old_node_id, const Record &key, page_id_t new_node_id)
{
  auto old_guard = buffer_pool_manager_->FetchPageRead(index_id_, old_node_id);
  auto old_node = reinterpret_cast<const BPTreePage *>(old_guard.GetData());

  if (old_node->IsRoot()) 
  {
    InsertIntoNewRoot(old_node_id, key, new_node_id);
    return;
  }
  page_id_t parent_page_id = old_node->GetParentPageId();


  auto parent_guard = buffer_pool_manager_->FetchPageWrite(index_id_, parent_page_id);
  auto parent = reinterpret_cast<BPTreeInternalPage *>(parent_guard.GetMutableData());

  if (parent->GetSize() < parent->GetMaxSize()) // 1️⃣ 父节点未满，直接插
  {
    parent->InsertNodeAfter(old_node_id, key, new_node_id);
    
    //debug
    std::cout << "父节点未满，直接插 ===parent insert ===" << std::endl;
    DebugPrintInternal(parent, key_schema_); 
    return;
  }

  // 父节点满
  // split internal
  
  page_id_t new_parent_page_id = NewPage();
  auto new_parent_guard = buffer_pool_manager_->FetchPageWrite(index_id_, new_parent_page_id);
  auto new_parent = reinterpret_cast<BPTreeInternalPage *>(new_parent_guard.GetMutableData());

  auto header_guard = buffer_pool_manager_->FetchPageRead(index_id_, FILE_HEADER_PAGE_ID);
  auto header = reinterpret_cast<const BPTreeIndexHeader *>(header_guard.GetData());

  new_parent->Init(index_id_, new_parent_page_id,parent->GetParentPageId(),header->key_size_, header->internal_max_size_);

  std::cout<<"内部节点需要分裂了"<<std::endl;
  
  // 3️⃣ 先插，再 split（非常重要）
  parent->InsertNodeAfter(old_node_id, key, new_node_id);

  // 4️⃣ 取 middle key
  int mid = parent->GetSize() / 2;
  Record middle_key(key_schema_, nullptr, parent->KeyAt(mid), INVALID_RID);

  // 5️⃣ split
  parent->MoveHalfTo(new_parent, buffer_pool_manager_);

  DebugPrintInternal(parent, key_schema_); 
  DebugPrintInternal(new_parent, key_schema_); 
  // middle key 上推
 // Record middle_key(key_schema_, nullptr, new_parent->KeyAt(0), INVALID_RID);
  InsertIntoParent(parent_page_id, middle_key, new_parent_page_id);
}
*/

void BPTreeIndex::InsertIntoNewRoot(page_id_t old_root_id, const Record &key, page_id_t new_page_id)
{
  page_id_t root_page_id = NewPage();
  auto root_guard = buffer_pool_manager_->FetchPageWrite(index_id_, root_page_id);
  auto root = reinterpret_cast<BPTreeInternalPage *>(root_guard.GetMutableData());

  auto header_guard = buffer_pool_manager_->FetchPageRead(index_id_, FILE_HEADER_PAGE_ID);
  auto header = reinterpret_cast<const BPTreeIndexHeader *>(header_guard.GetData());

  root->Init(index_id_, root_page_id, INVALID_PAGE_ID,
             header->key_size_, header->internal_max_size_);

  root->PopulateNewRoot(old_root_id, key, new_page_id);

  // 更新孩子 parent

  auto left = buffer_pool_manager_->FetchPageWrite(index_id_, old_root_id);
  reinterpret_cast<BPTreePage *>(left.GetMutableData())->SetParentPageId(root_page_id);

  auto right = buffer_pool_manager_->FetchPageWrite(index_id_, new_page_id);
  reinterpret_cast<BPTreePage *>(right.GetMutableData())->SetParentPageId(root_page_id);


  auto header_guard2 = buffer_pool_manager_->FetchPageWrite(index_id_, FILE_HEADER_PAGE_ID);
  auto header2 = reinterpret_cast<BPTreeIndexHeader *>(header_guard2.GetMutableData());
  header2->root_page_id_ = root_page_id;
  header2->tree_height_++;

    //debug
  DebugPrintInternal(root, key_schema_); 
}

void BPTreeIndex::Insert(const Record &key, const RID &rid) 
{ 
  std::unique_lock lock(index_latch_);

  if (IsEmpty()) 
  {
    StartNewTree(key, rid);
    return;
  }

  InsertIntoLeaf(key, rid);
}

auto BPTreeIndex::Delete(const Record &key) -> bool
{
    std::unique_lock lock(index_latch_);

  //  std::cout << "Delete key is" << key.ToString() << std::endl;

    if (IsEmpty()) 
    {
      std::cout<<"树是空的"<<std::endl;
      return false;
    }
    // 1 找到 key 所在叶子页
    page_id_t leaf_page_id = FindLeafPage(key);
    if (leaf_page_id == INVALID_PAGE_ID) 
    {
      std::cout<<"没找到这个键:"<<key.ToString()<<"对应的页"<<std::endl;
      return false;
    }
    auto leaf_guard = buffer_pool_manager_->FetchPageWrite(index_id_, leaf_page_id);
    auto leaf = reinterpret_cast<BPTreeLeafPage *>(leaf_guard.GetMutableData());

    DebugPrintLeaf(leaf,key_schema_);

    // 2 删除记录
    int old_size = leaf->GetSize();
    leaf->RemoveRecord(key, key_schema_);
    if (leaf->GetSize() == old_size) 
    {
     // std::cout<<"这个键:"<<key.ToString()<<"删除后叶子大小没变！"<<std::endl;
      return false; // key 不存在
    }
    // 更新 header
    auto header_guard = buffer_pool_manager_->FetchPageWrite(index_id_, FILE_HEADER_PAGE_ID);
    auto header = reinterpret_cast<BPTreeIndexHeader *>(header_guard.GetMutableData());
    header->num_entries_--;

    // 3 检查 leaf 是否需要合并或借位12
    if (!leaf->IsRoot() && !leaf->IsSafe(false)) 
    {
  //    std::cout<<"leaf 需要合并或借位"<<std::endl;
      CoalesceOrRedistribute(leaf_page_id);
    }
    else if (leaf->IsRoot() && leaf->GetSize() == 0) 
    {
     // std::cout<<"leaf 是根节点而且删完为空"<<std::endl;
      AdjustRoot(leaf);
    }

    return true;
}

auto BPTreeIndex::CoalesceOrRedistribute(page_id_t node_id) -> bool
{
  bool need_coalesce = false;
  page_id_t neighbor_id = INVALID_PAGE_ID;
  page_id_t parent_id = INVALID_PAGE_ID;
  int index = 0;

  {
    auto node_guard = buffer_pool_manager_->FetchPageWrite(index_id_, node_id);
    auto node = reinterpret_cast<BPTreePage *>(node_guard.GetMutableData());

    if (node->IsRoot()) 
    {
      return AdjustRoot(node);
    }

    parent_id = node->GetParentPageId();
    auto parent_guard = buffer_pool_manager_->FetchPageWrite(index_id_, parent_id);
    auto parent = reinterpret_cast<BPTreeInternalPage *>(parent_guard.GetMutableData());

    // 找到 node 在 parent 中的位置
    //int index = 0;
    while (index < parent->GetSize() && parent->ValueAt(index) != node_id) index++;

    neighbor_id = (index == 0) ? parent->ValueAt(1) : parent->ValueAt(index - 1);
    auto neighbor_guard = buffer_pool_manager_->FetchPageWrite(index_id_, neighbor_id);
    auto neighbor_node = reinterpret_cast<BPTreePage *>(neighbor_guard.GetMutableData());

    //std::cout<<"node:"<<node_id<<" neighbor_node_id:"<<neighbor_id<<std::endl;

    // 判断能否重分配
    if (neighbor_node->GetSize() > (neighbor_node->GetMaxSize() / 2)) 
    {
     // std::cout<<"能够重分配:"<<neighbor_id<<" "<<node_id<<std::endl;
      Redistribute(neighbor_node, node, index);
  
      //debug
    //  std::cout<<"重分配后的信息:"<<std::endl;
      if(node->IsLeaf())
      {
        DebugPrintLeaf(reinterpret_cast<BPTreeLeafPage *>(node),key_schema_);
        DebugPrintLeaf(reinterpret_cast<BPTreeLeafPage *>(neighbor_node),key_schema_);
      }
      else
      {
        DebugPrintInternal(reinterpret_cast<BPTreeInternalPage *>(node),key_schema_);
        DebugPrintInternal(reinterpret_cast<BPTreeInternalPage *>(neighbor_node),key_schema_);
      }
      DebugPrintInternal(parent,key_schema_);
      return true;
    } 
    else 
    {
      //std::cout<<"无法重分配，准备合并两个结点:"<<std::endl;
      //return Coalesce(neighbor_id, node_id, parent_id, index);
      need_coalesce=true;
    }
  }
  if(need_coalesce)
  {
    return Coalesce(neighbor_id, node_id, parent_id, index);
  }
  return true;
}

auto BPTreeIndex::Coalesce(page_id_t neighbor_node_id, page_id_t node_id, page_id_t parent_id, int index) -> bool
{
  bool digui=false;
  {
      auto node_guard =
          buffer_pool_manager_->FetchPageWrite(index_id_, node_id);
      auto node =
          reinterpret_cast<BPTreePage *>(node_guard.GetMutableData());

      auto neighbor_guard =
          buffer_pool_manager_->FetchPageWrite(index_id_, neighbor_node_id);
      auto neighbor_node =
          reinterpret_cast<BPTreePage *>(neighbor_guard.GetMutableData());

      {
          auto parent_guard =
              buffer_pool_manager_->FetchPageWrite(index_id_, parent_id);
          auto parent =
              reinterpret_cast<BPTreeInternalPage *>(parent_guard.GetMutableData());

          BPTreePage *left = (index == 0) ? node : neighbor_node;
          BPTreePage *right = (index == 0) ? neighbor_node : node;

          Record middle_key(
              key_schema_, nullptr,
              parent->KeyAt(index == 0 ? 1 : index),
              INVALID_RID
          );

          if (left->IsLeaf())
          {
              auto left_leaf = reinterpret_cast<BPTreeLeafPage *>(left);
              auto right_leaf = reinterpret_cast<BPTreeLeafPage *>(right);
              right_leaf->MoveAllTo(left_leaf);
              left_leaf->SetNextPageId(right_leaf->GetNextPageId());
          }
          else
          {
              auto left_internal =
                  reinterpret_cast<BPTreeInternalPage *>(left);
              auto right_internal =
                  reinterpret_cast<BPTreeInternalPage *>(right);
              right_internal->MoveAllTo(left_internal, middle_key,
                                        buffer_pool_manager_);
          }

          parent->SetSize(parent->GetSize() - 1);

          if (index == 0)
          {
              for (int i = index; i < parent->GetSize(); i++)
              {
                  if (i != 0)
                  {
                      parent->SetKeyAt(i, parent->KeyAt(i + 1));
                  }
                  parent->SetValueAt(i + 1, parent->ValueAt(i + 2));
              }
          }
          else
          {
              for (int i = index; i < parent->GetSize(); i++)
              {
                  parent->SetKeyAt(i, parent->KeyAt(i + 1));
                  parent->SetValueAt(i, parent->ValueAt(i + 1));
              }
          }

      //    std::cout << "合并后节点信息如下:" << std::endl;
          if (left->IsLeaf())
          {
              DebugPrintLeaf(reinterpret_cast<BPTreeLeafPage *>(left), key_schema_);
              DebugPrintInternal(parent, key_schema_);
          }
          else
          {
              DebugPrintInternal(reinterpret_cast<BPTreeInternalPage *>(left), key_schema_);
              DebugPrintInternal(parent, key_schema_);
          }

          if (!parent->IsSafe(false))
          {
        //      std::cout << "父节点不安全需要递归处理" << std::endl;
              digui=true;
              //CoalesceOrRedistribute(parent_id);
          }
      } // parent_guard 在这里析构
  }
  if(digui)
  {
      CoalesceOrRedistribute(parent_id);
  }
  return true;
}

void BPTreeIndex::Redistribute(BPTreePage *neighbor_node, BPTreePage *node, int index) 
{ 
  // 判断 node 类型
    if (node->IsLeaf()) 
    {
        // 叶子节点借位
        auto leaf = reinterpret_cast<BPTreeLeafPage *>(node);
        auto neighbor_leaf = reinterpret_cast<BPTreeLeafPage *>(neighbor_node);

        if (index == 0) 
        {
            // node 在左，neighbor 在右，从 neighbor 左边借
            Record borrowed_key(key_schema_, nullptr, neighbor_leaf->KeyAt(0), INVALID_RID);
            RID borrowed_value = neighbor_leaf->ValueAt(0);

            // 插入到 node 末尾
            leaf->Insert(borrowed_key, borrowed_value, key_schema_);

            // neighbor 左移
            for (int i = 1; i < neighbor_leaf->GetSize(); i++) 
            {
                neighbor_leaf->SetKeyAt(i - 1, neighbor_leaf->KeyAt(i));
                neighbor_leaf->SetValueAt(i - 1, neighbor_leaf->ValueAt(i));
            }
            neighbor_leaf->SetSize(neighbor_leaf->GetSize() - 1);

            // 更新父节点 key
            auto parent_guard = buffer_pool_manager_->FetchPageWrite(index_id_, leaf->GetParentPageId());
            auto parent = reinterpret_cast<BPTreeInternalPage *>(parent_guard.GetMutableData());
            parent->SetKeyAt(index+1, neighbor_leaf->KeyAt(0));
        } 
        else 
        {
            // node 在右，neighbor 在左，从 neighbor 右边借
            int last = neighbor_leaf->GetSize() - 1;
            Record borrowed_key(key_schema_, nullptr, neighbor_leaf->KeyAt(last), INVALID_RID);
            RID borrowed_value = neighbor_leaf->ValueAt(last);

            // 插入 node 前面
            for (int i = leaf->GetSize() - 1; i >= 0; i--) 
            {
                leaf->SetKeyAt(i + 1, leaf->KeyAt(i));
                leaf->SetValueAt(i + 1, leaf->ValueAt(i));
            }
            leaf->SetKeyAt(0, borrowed_key.GetData());
            leaf->SetValueAt(0, borrowed_value);
            leaf->SetSize(leaf->GetSize() + 1);

            neighbor_leaf->SetSize(neighbor_leaf->GetSize() - 1);

            // 更新父节点 key
            auto parent_guard = buffer_pool_manager_->FetchPageWrite(index_id_, leaf->GetParentPageId());
            auto parent = reinterpret_cast<BPTreeInternalPage *>(parent_guard.GetMutableData());
            parent->SetKeyAt(index, leaf->KeyAt(0));
        }
    } 
    else 
    {
        // 内部节点借位
        auto internal = reinterpret_cast<BPTreeInternalPage *>(node);
        auto neighbor_internal = reinterpret_cast<BPTreeInternalPage *>(neighbor_node);

        auto parent_guard = buffer_pool_manager_->FetchPageWrite(index_id_, internal->GetParentPageId());
        auto parent = reinterpret_cast<BPTreeInternalPage *>(parent_guard.GetMutableData());

        if (index == 0) 
        {
            // node 在左，neighbor 在右
            int neighbor_first_index = 0;
            Record parent_key(key_schema_, nullptr, parent->KeyAt(index+1), INVALID_RID);

            // 从 parent key 下推到 node
            internal->SetKeyAt(internal->GetSize(), parent_key.GetData());
            internal->SetValueAt(internal->GetSize(), neighbor_internal->ValueAt(0));
            internal->SetSize(internal->GetSize() + 1);
            //记得修改新子节点的parent_id       注意子节点不一定是叶节点也可能是内部节点
            auto newchild_guard = buffer_pool_manager_->FetchPageWrite(index_id_, neighbor_internal->ValueAt(0));
            auto newchild = reinterpret_cast<BPTreePage *>(newchild_guard .GetMutableData());
            newchild->SetParentPageId(internal->GetPageId());

            // 更新父节点 key
            parent->SetKeyAt(index+1, neighbor_internal->KeyAt(1));

            for (int i = 1; i < neighbor_internal->GetSize(); i++) 
            {
                neighbor_internal->SetValueAt(i - 1, neighbor_internal->ValueAt(i));
            }
            for (int i = 1; i < neighbor_internal->GetSize()-1; i++) 
            {
                neighbor_internal->SetKeyAt(i, neighbor_internal->KeyAt(i+1));              
            }
            neighbor_internal->SetSize(neighbor_internal->GetSize() - 1);
        } 
        else //index !=0
        {
            // node 在右，neighbor 在左
            int neighbor_last_index = neighbor_internal->GetSize() - 1;
            Record parent_key(key_schema_, nullptr, parent->KeyAt(index), INVALID_RID);

            // 插入 node 前
            for (int i = internal->GetSize() - 1; i >= 0; i--) 
            {
                internal->SetValueAt(i + 1, internal->ValueAt(i));
            }
            // 插入 node 前
            for (int i = internal->GetSize() - 1; i >= 1; i--) 
            {
                internal->SetKeyAt(i + 1, internal->KeyAt(i));
            }

            internal->SetKeyAt(1, parent_key.GetData());
            internal->SetValueAt(0, neighbor_internal->ValueAt(neighbor_last_index));
            internal->SetSize(internal->GetSize() + 1);
            //记得修改新子节点的parent_id       注意子节点不一定是叶节点也可能是内部节点
            auto newchild_guard = buffer_pool_manager_->FetchPageWrite(index_id_, neighbor_internal->ValueAt(neighbor_last_index));
            auto newchild = reinterpret_cast<BPTreePage *>(newchild_guard .GetMutableData());
            newchild->SetParentPageId(internal->GetPageId());


            // 更新父节点 key
            parent->SetKeyAt(index, neighbor_internal->KeyAt(neighbor_internal->GetSize() - 1));
            neighbor_internal->SetSize(neighbor_last_index);
        }
    }
}

auto BPTreeIndex::AdjustRoot(BPTreePage *old_root_node) -> bool
{
    if (old_root_node->IsLeaf() && old_root_node->GetSize() == 0) //如果根节点为空叶子节点，树变空
    {
      //  std::cout<<"根节点为空叶子节点，树变空"<<std::endl;

        auto header_guard = buffer_pool_manager_->FetchPageWrite(index_id_, FILE_HEADER_PAGE_ID);
        auto header = reinterpret_cast<BPTreeIndexHeader *>(header_guard.GetMutableData());
        header->root_page_id_ = INVALID_PAGE_ID;
        header->tree_height_ = 0;
        return true;
    }
    if (!old_root_node->IsLeaf() && old_root_node->GetSize() == 1) //如果根节点是只有一个子节点的内部节点，子节点成为新根
    {
       // std::cout<<"根节点是只有一个子节点的内部节点，子节点成为新根"<<std::endl;

        auto internal = reinterpret_cast<BPTreeInternalPage *>(old_root_node);
        page_id_t new_root_id = internal->ValueAt(0);
        auto new_root_guard = buffer_pool_manager_->FetchPageWrite(index_id_, new_root_id);
        auto new_root = reinterpret_cast<BPTreePage *>(new_root_guard.GetMutableData());
        new_root->SetParentPageId(INVALID_PAGE_ID);

        auto header_guard = buffer_pool_manager_->FetchPageWrite(index_id_, FILE_HEADER_PAGE_ID);
        auto header = reinterpret_cast<BPTreeIndexHeader *>(header_guard.GetMutableData());
        header->root_page_id_ = new_root_id;
        header->tree_height_--;
        return true;
    }
    return false;
}

auto BPTreeIndex::Search(const Record &key) -> std::vector<RID> 
{ 
  std::shared_lock lock(index_latch_);

  page_id_t leaf_id = FindLeafPage(key,false);
  if (leaf_id == INVALID_PAGE_ID) 
  {
    return {};
  }

  auto leaf_guard = buffer_pool_manager_->FetchPageRead(index_id_, leaf_id);
  auto leaf = reinterpret_cast<const BPTreeLeafPage *>(leaf_guard.GetData());

  return leaf->Lookup(key, key_schema_); 
}

auto BPTreeIndex::SearchRange(const Record &low_key, const Record &high_key) -> std::vector<RID>
{
  std::shared_lock lock(index_latch_);
  std::vector<RID> result;

  page_id_t leaf_id = FindLeafPageForRange(low_key, true);
  bool first_leaf = true;

  while (leaf_id != INVALID_PAGE_ID) {
    auto guard = buffer_pool_manager_->FetchPageRead(index_id_, leaf_id);
    auto leaf = reinterpret_cast<const BPTreeLeafPage *>(guard.GetData());

    int start = 0;
    if (first_leaf) {
      start = leaf->LowerBound(low_key, key_schema_);
      first_leaf = false;
    }

    for (int i = start; i < leaf->GetSize(); i++) {
      Record key(key_schema_, nullptr, leaf->KeyAt(i), INVALID_RID);

      if (Record::Compare(key, high_key) > 0) {
        return result;
      }
      result.push_back(leaf->ValueAt(i));
    }

    leaf_id = leaf->GetNextPageId();
  }
  return result;
}

// Iterator implementation
BPTreeIndex::BPTreeIterator::BPTreeIterator(BPTreeIndex *tree, page_id_t leaf_page_id, int index)
    : tree_(tree), leaf_page_id_(leaf_page_id), index_(index)
{}

auto BPTreeIndex::BPTreeIterator::IsValid() -> bool
{
    if (leaf_page_id_ == INVALID_PAGE_ID) return false;

    auto guard = tree_->buffer_pool_manager_->FetchPageRead(tree_->index_id_, leaf_page_id_);
    auto leaf = reinterpret_cast<const BPTreeLeafPage *>(guard.GetData());
    return index_ >= 0 && index_ < leaf->GetSize();
}

void BPTreeIndex::BPTreeIterator::Next()
{
  if (!IsValid()) 
  {
    return;
  }

  auto guard =tree_->buffer_pool_manager_->FetchPageRead(tree_->index_id_, leaf_page_id_);
  auto leaf = reinterpret_cast<const BPTreeLeafPage *>(guard.GetData());

  index_++;

  // 当前 leaf 还有 key
  if (index_ < leaf->GetSize()) 
  {
    return;
  }

  //  当前 leaf 用完，跳下一个
  page_id_t next_leaf = leaf->GetNextPageId();
  if (next_leaf == INVALID_PAGE_ID) 
  {
    leaf_page_id_ = INVALID_PAGE_ID;
    return;
  }

  leaf_page_id_ = next_leaf;
  index_ = 0;

  //  防御：下一个 leaf 是空
  auto next_guard =tree_->buffer_pool_manager_->FetchPageRead(tree_->index_id_, leaf_page_id_);
  auto next_leaf_page =reinterpret_cast<const BPTreeLeafPage *>(next_guard.GetData());

  if (next_leaf_page->GetSize() == 0) 
  {
    leaf_page_id_ = INVALID_PAGE_ID;
  }
}

auto BPTreeIndex::BPTreeIterator::GetKey() -> Record
{
  auto guard = tree_->buffer_pool_manager_->FetchPageRead(tree_->index_id_, leaf_page_id_);
  auto leaf = reinterpret_cast<const BPTreeLeafPage *>(guard.GetData());
  return Record(tree_->key_schema_, nullptr,leaf->KeyAt(index_),INVALID_RID);
}

auto BPTreeIndex::BPTreeIterator::GetRID() -> RID
{
  auto guard = tree_->buffer_pool_manager_->FetchPageRead(tree_->index_id_, leaf_page_id_);
  auto leaf = reinterpret_cast<const BPTreeLeafPage *>(guard.GetData());
  return leaf->ValueAt(index_);
}

auto BPTreeIndex::Begin() -> std::unique_ptr<IIterator>
{
  if (IsEmpty()) 
  {
    return End();
  }

// 分配一块“假的但合法的”key buffer
  std::vector<char> dummy_buf(key_schema_->GetRecordLength(), 0);
  Record dummy(key_schema_, nullptr, dummy_buf.data(), INVALID_RID);

  page_id_t leaf_page_id = FindLeafPage(dummy, true);
  return std::make_unique<BPTreeIterator>(this, leaf_page_id, 0);
}

auto BPTreeIndex::Begin(const Record &key) -> std::unique_ptr<IIterator>
{
 if (IsEmpty()) return End();

    page_id_t leaf_page_id = FindLeafPage(key, false);
    while (leaf_page_id != INVALID_PAGE_ID) {
        auto guard = buffer_pool_manager_->FetchPageRead(index_id_, leaf_page_id);
        auto leaf = reinterpret_cast<const BPTreeLeafPage *>(guard.GetData());

        int index = leaf->LowerBound(key, key_schema_);
        if (index < leaf->GetSize()) {
            return std::make_unique<BPTreeIterator>(this, leaf_page_id, index);
        }

        // 当前 leaf 全部小于 key，跳到下一个 leaf
        leaf_page_id = leaf->GetNextPageId();
    }

    return End();
}

auto BPTreeIndex::End() -> std::unique_ptr<IIterator>
{
  return std::make_unique<BPTreeIterator>(this, INVALID_PAGE_ID, 0);
}

void BPTreeIndex::Clear()
{
  NJUDB_STUDENT_TODO(l4, t1);
}

void BPTreeIndex::ClearPage(page_id_t page_id)
{
  NJUDB_STUDENT_TODO(l4, t1);
}

auto BPTreeIndex::IsEmpty() -> bool
{
  auto guard = buffer_pool_manager_->FetchPageRead(index_id_, FILE_HEADER_PAGE_ID);
  auto header = reinterpret_cast<const BPTreeIndexHeader *>(guard.GetData());
  return header->num_entries_ == 0;
}

auto BPTreeIndex::Size() -> size_t
{
  auto guard = buffer_pool_manager_->FetchPageRead(index_id_, FILE_HEADER_PAGE_ID);
  auto header = reinterpret_cast<const BPTreeIndexHeader *>(guard.GetData());
  return header->num_entries_;
}

auto BPTreeIndex::GetHeight() -> int
{
  auto guard = buffer_pool_manager_->FetchPageRead(index_id_, FILE_HEADER_PAGE_ID);
  auto header = reinterpret_cast<const BPTreeIndexHeader *>(guard.GetData());
  return header->tree_height_;
}

}  // namespace njudb
