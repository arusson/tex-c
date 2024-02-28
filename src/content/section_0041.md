# Section 41

The length of the current string is called *cur_length*:

```c include/strings.h
#define cur_length (pool_ptr - str_start[str_ptr])
```