# Dynamic‑Allocated Sequence List
> Dynamic sequential list implemented in C and C++.
> This repository contains three iterative versions: original bug‑prone C, optimized robust C, and C++ object‑oriented class implementation.

## File Overview
| Filename       | Language | Description                                                  |
| -------------- | -------- | ------------------------------------------------------------ |
| `seq_list1.c`  | C        | Initial naive implementation. Implements basic CRUD, **with known defects and bugs**. |
| `seq_list2.c`  | C        | Optimized production‑style C version. Complete memory management, full boundary check, richer API. |
| `seq_list.cpp` | C++      | OOP class‑wrapped version. Encapsulated data members, constructor / destructor auto memory management. |

## Core Concept
Dynamic sequence list stores elements on heap via continuous dynamic array.
- `data`: pointer points to dynamically‑allocated element array
- `length`: number of **valid elements**, not the max capacity
- `MAXSIZE`: static upper‑bound capacity of this implementation
> Note: **logic position starts from 1**, internal array subscript starts from 0. Conversion formula: `array_index = logic_pos - 1`.

## API Reference

### ✅ Optimized C version (`seq_list2.c`)
```c
// create empty seqlist, return NULL if malloc fails
SeqList* initList();

// destroy list and free heap memory, eliminate wild pointer
void destroyList(SeqList** L);

// logical clear elements, keep allocated memory
void clearList(SeqList* L);

// append element to tail, return 1‑success / 0‑fail
int appendElem(SeqList* L, ElemType e);

// insert element at logic position pos [1 ~ length+1]
int insertElem(SeqList* L, int pos, ElemType e);

// delete element at pos, deleted value output via *e
int deleteElem(SeqList* L, int pos, ElemType* e);

// find first occurrence, return logic position; return 0 if not found
int findFirstElem(SeqList* L, ElemType e);

// print all logic positions matching value e
void findAllElem(SeqList* L, ElemType e);

// get element by logic position
int getElem(SeqList* L, int pos, ElemType* e);

// traverse and print all valid elements
void listElem(SeqList* L);
✅ C++ OOP Version (seq_list.cpp)
All methods encapsulated inside class SeqList.
cpp
运行
// constructor: auto allocate memory
SeqList();

// destructor: auto release heap memory when object out‑of‑scope
~SeqList();

void clearList();
bool appendElem(ElemType e);
bool insertElem(int pos, ElemType e);
bool deleteElem(int pos, ElemType& e);
int findFirstElem(ElemType e) const;
void findAllElem(ElemType e) const;
bool getElem(int pos, ElemType& e) const;
void listElem() const;
int getLength() const;
Time Complexity
表格
Operation	Complexity	Note
Random access by position	
O(1)
continuous memory, direct subscript access
Tail append	
O(1)
no element shift
Middle insert / delete	
O(n)
cost comes from element moving
Search by value	
O(n)
linear scan
Compile & Run Commands
bash
# compile original bug‑version C
gcc seq_list1.c -o seq_list1
./seq_list1

# compile optimized C version
gcc seq_list2.c -o seq_list2
./seq_list2

# compile C++ class version
g++ seq_list.cpp -o seq_list_cpp
./seq_list_cpp
Known Defects in seq_list1.c (Original naive code)
Memory leak: malloc() without corresponding free().
Insert position validation error: cannot insert at the tail of list. Valid range should be 1 ~ length+1.
Missing NULL pointer check. Passing NULL pointer will trigger segment fault.
Misuse sizeof(list->data) to calculate array size. data is pointer, returns pointer size(8‑byte on 64‑bit platform).
No return‑value check for malloc(). Allocation failure leads to undefined behavior.
Important Pitfalls & Notes
For C version initList(): two times malloc(). If array allocation fails, remember to free the already‑allocated SeqList struct to avoid memory leak.
destroyList() receives double pointer, to set external pointer to NULL after free, prevent wild pointer.
In C++, destructor will be invoked automatically when local object goes out of scope, manual memory release is not required.
In C++, use const qualifier for read‑only member functions to guarantee object state unchanged.
Logic position starts at 1, always convert to pos‑1 for array subscript.
Learning Points
Heap dynamic memory management: malloc/free vs new[]/delete[]
Defensive programming: NULL‑check, boundary‑check for all public interfaces
C procedural style vs C++ object‑oriented encapsulation
Difference between logical position and physical array index
Source code iterative evolution: from minimal working prototype to robust production‑level code
plaintext

### 使用说明
1. 将上面全部文本复制，新建文件命名：`README.md`，放在 `ds/seqlist/` 同一目录。
2. git提交命令：
```bash
git add ds/seqlist/README.md
git commit -m "docs: complete readme for dynamic seqlist module"
git push