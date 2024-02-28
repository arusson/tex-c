// ~~~ Section 40 ~~~
// ~~~ Start file |strings.h|, 1381 ~~~
#ifndef STRINGS_H_
#define STRINGS_H_

#include "tex.h"
// ~~~ End section 1381 ~~~

#define length(X) (str_start[(X) + 1] - str_start[(X)]) // the number of characters in string number X
// ~~~ End section 40 ~~~

// ~~~ Section 41 ~~~
#define cur_length (pool_ptr - str_start[str_ptr])
// ~~~ End section 41 ~~~

// ~~~ Section 42 ~~~
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
// ~~~ End section 42 ~~~

// ~~~ Section 44 ~~~
#define flush_string decr(str_ptr); pool_ptr = str_start[str_ptr]
// ~~~ End section 44 ~~~

// ~~~ Section 48 ~~~
#define app_lc_hex(X)                  \
    do {                               \
        l = (X);                       \
        if (l < 10) {                  \
            append_char(l + '0');      \
        }                              \
        else {                         \
            append_char(l - 10 + 'a'); \
        }                              \
    } while (0)
// ~~~ End section 48 ~~~

// ~~~ Section 1381 ~~~
// current string enters the pool
str_number make_string();

// test equality of strings
int str_eq_buf(str_number s, int k);

// test equality of strings
int str_eq_str(str_number s, str_number t);

#ifdef INIT
// initializes the string pool
void get_strings_started();
#endif

str_number put_string(char *s);

#endif
// ~~~ End section 1381 ~~~
