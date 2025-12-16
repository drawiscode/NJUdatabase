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
  //return;
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
  //return;
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
    if((size_-1)<(max_size_/2))
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
  recipient->SetNextPageId(GetNextPageId());// not sure

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
   { auto guard = bpm->FetchPageWrite(index_id_, ValueAt(i));
    //auto child = reinterpret_cast<BPTreePage *>(guard.GetData());
    auto child = reinterpret_cast<BPTreePage *>(guard.GetMutableData());

    std::cout<<"子节点id:"<<child->GetPageId()<<std::endl;
    std::cout<<"正确的父节点id:"<<GetPageId()<<std::endl;

    child->SetParentPageId(GetPageId());
   }
  }
}

void BPTreeInternalPage::MoveAllTo(BPTreeInternalPage *recipient, const Record &middle_key, BufferPoolManager *bpm)
{
  // For internal nodes, we need to merge:
  // 1. The middle key from the parent (this becomes a key in the recipient)
  // 2. All keys and children from the source node
  recipient->SetKeyAt(recipient->GetSize(), middle_key.GetData());
  recipient->SetValueAt(recipient->GetSize(), ValueAt(0));
  recipient->SetSize(recipient->GetSize() + 1);

  CopyNFrom(GetKeysArray() + key_size_, GetChildrenArray() + 1, GetSize() - 1, bpm);
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
  NJUDB_STUDENT_TODO(l4, t1);
  return INVALID_PAGE_ID;
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
  std::cout<<"After leaf split :"<<std::endl;
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

  /* ---------- 1️⃣ 只读 old_node，用完立刻释放 ---------- */
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
  } //  old_guard 在这里析构（Unpin）

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

      // debug
      std::cout << "父节点未满，直接插 ===parent insert ===" << std::endl;
      DebugPrintInternal(parent, key_schema_);

      return; //  parent_guard 析构
    }

    /* ---------- 父节点满：需要 split ---------- */
    std::cout << "内部节点需要分裂了" << std::endl;

    // 先插再 split（非常重要）
    parent->InsertNodeAfter(old_node_id, key, new_node_id);

    // 创建新 internal page
    new_parent_page_id = NewPage();
    auto new_parent_guard =
        buffer_pool_manager_->FetchPageWrite(index_id_, new_parent_page_id);
    auto new_parent =
        reinterpret_cast<BPTreeInternalPage *>(new_parent_guard.GetMutableData());

    // 读 header
    auto header_guard =
        buffer_pool_manager_->FetchPageRead(index_id_, FILE_HEADER_PAGE_ID);
    auto header =
        reinterpret_cast<const BPTreeIndexHeader *>(header_guard.GetData());

    new_parent->Init(index_id_,
                     new_parent_page_id,
                     parent->GetParentPageId(),
                     header->key_size_,
                     header->internal_max_size_);

    // 取 middle key（在 split 前）
    int mid = parent->GetSize() / 2;
    middle_key =
        Record(key_schema_, nullptr, parent->KeyAt(mid), INVALID_RID);

    // split
    parent->MoveHalfTo(new_parent, buffer_pool_manager_);

    DebugPrintInternal(parent, key_schema_);
    DebugPrintInternal(new_parent, key_schema_);

  } // ✅ parent_guard / new_parent_guard / header_guard 全部在这里析构

  /* ----------  递归向上（此时不再持有任何 PageGuard） ---------- */
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
  NJUDB_STUDENT_TODO(l4, t1);
  return false;
}

auto BPTreeIndex::CoalesceOrRedistribute(page_id_t node_id) -> bool
{
  NJUDB_STUDENT_TODO(l4, t1);
  return false;
}

auto BPTreeIndex::Coalesce(page_id_t neighbor_node_id, page_id_t node_id, page_id_t parent_id, int index) -> bool
{
  // Fetch all pages needed for coalescing
  NJUDB_STUDENT_TODO(l4, t1);
  return false;
}

void BPTreeIndex::Redistribute(BPTreePage *neighbor_node, BPTreePage *node, int index) { NJUDB_STUDENT_TODO(l4, t1); }

auto BPTreeIndex::AdjustRoot(BPTreePage *old_root_node) -> bool
{
  NJUDB_STUDENT_TODO(l4, t1);
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
  while (leaf_id != INVALID_PAGE_ID) 
  {
    auto leaf_guard = buffer_pool_manager_->FetchPageRead(index_id_, leaf_id);
    auto leaf = reinterpret_cast<const BPTreeLeafPage *>(leaf_guard.GetData());

    for (int i = 0; i < leaf->GetSize(); i++) 
    {
      Record key(key_schema_,nullptr,leaf->KeyAt(i),INVALID_RID);
      if (Record::Compare(key, high_key) > 0) 
      {
        return result;
      }
      if (Record::Compare(key, low_key) >= 0) 
      {
        result.push_back(leaf->ValueAt(i));
      }
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
  return leaf_page_id_ != INVALID_PAGE_ID;
}

void BPTreeIndex::BPTreeIterator::Next()
{
  auto guard = tree_->buffer_pool_manager_->FetchPageRead(tree_->index_id_, leaf_page_id_);
  auto leaf = reinterpret_cast<const BPTreeLeafPage *>(guard.GetData());

  index_++;
  if (index_ >= leaf->GetSize()) 
  {
    leaf_page_id_ = leaf->GetNextPageId();
    index_ = 0;
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
  if (IsEmpty()) 
  {
    return End();
  }

  page_id_t leaf_page_id = FindLeafPage(key,false);
  auto guard = buffer_pool_manager_->FetchPageRead(index_id_, leaf_page_id);
  auto leaf = reinterpret_cast<const BPTreeLeafPage *>(guard.GetData());

  int index = leaf->LowerBound(key, key_schema_);

  return std::make_unique<BPTreeIterator>(this,leaf_page_id, index);
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
