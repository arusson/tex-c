# Section 271

```c << Global variables >>+=
memory_word save_stack[SAVE_SIZE + 1];
int save_ptr;          // first unused entry on |save_stack|
int max_save_stack;    // maximum usage of save stack
quarterword cur_level; // current nesting level for groups
int cur_group;         // current group type
int cur_boundary;      // where the current level begins
```
