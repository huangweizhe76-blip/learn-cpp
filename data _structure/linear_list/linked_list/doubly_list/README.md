# Doubly Linked List (Sentinel‑Head)

C & C++ implementation of doubly linked list with dummy head.

## Files
- `doubly_linked_list1.c`: Initial buggy C code
- `doubly_linked_list2.c`: Fixed stable C version
- `doubly_linked_list.cpp`: C++ class RAII version
- `note.md`: Chinese bug & summary notes

## Functions
Head insert / Tail insert / Pos‑based insert & delete / Traverse / Memory release

## Complexity
| Op            | Time |
| ------------- | ---- |
| Head insert   | O(1) |
| Tail / Pos op | O(n) |

## Compile
```bash
gcc doubly_linked_list2.c -o main_c
g++ doubly_linked_list.cpp -o main_cpp
./main_c
./main_cpp
Key pitfalls
Do not access nullptr->prev when inserting at list tail
Free sentinel head node to avoid memory leak
Modify both prev & next pointer for doubly‑linked‑list