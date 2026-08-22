# Singly Linked List

Versions:
- `single_list1.c`: Initial C implementation, contains several boundary‑case bugs
- `single_list2.c`: Fully‑fixed & optimized C implementation
- `single_list.cpp`: Object‑oriented C++ encapsulated version

## Features
- Head insertion, tail insertion
- Insert / delete by position index
- Linked‑list reversal
- Fast‑slow pointer for k‑th‑from‑last node
- Find middle node
- List reorder algorithm
- Detect intersection node of two linked lists
- Cycle detection & find cycle entry node

> Warning: For cyclic linked lists, **break the cycle manually before destruction**, otherwise memory‑free logic will fall into infinite loop.