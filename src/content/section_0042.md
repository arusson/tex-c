# Section 42

Strings are created by appending character codes to *str_pool*.
The *append_char* macro, defined here, does not check to see if the value of *pool_ptr* has gotten too high; this test is supposed to be made before *append_char* is used.
There is also a *flush_char* macro, which erases the last character appended.

To test if there is room to append *l* more characters to *str_pool*, we shall write *str_room(l)*, which aborts $\TeX$ and gives an apologetic error message if there isn't enough room.

```c include/strings.h
// put |ASCII_code| X at the end of |str_pool|
#define append_char(X) str_pool[pool_ptr] = (X); incr(pool_ptr)

// forget the last character in the pool
#define flush_char decr(pool_ptr)

// make sure that the pool hasn't overflowed
#define str_room(X)                                           \
    do {                                                      \
        if (pool_ptr + (X) > POOL_SIZE) {                     \
            overflow("pool size", POOL_SIZE - init_pool_ptr); \
        }                                                     \
    } while (0)
```