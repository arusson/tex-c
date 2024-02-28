# Section 39

```c << Global variables >>+=
ASCII_code   str_pool[POOL_SIZE + 1];    // the characters
pool_pointer str_start[MAX_STRINGS + 1]; // the starting pointers
pool_pointer pool_ptr;                   // first unused position in |str_pool|
str_number   str_ptr;                    // number of the current string being created
pool_pointer init_pool_ptr;              // the starting value of |pool_ptr|
str_number   init_str_ptr;               // the starting value of |str_ptr|
```
