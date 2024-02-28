# Section 43

Once a sequence of characters has been appended to *str_pool*, it officially becomes a string when the function *make_string* is called.
This function returns the identification number of the new string as its value.

```c strings.c
// current string enters the pool
str_number make_string() {
    if (str_ptr == MAX_STRINGS) {
        overflow("number of strings", MAX_STRINGS - init_str_ptr);
    }
    incr(str_ptr);
    str_start[str_ptr] = pool_ptr;
    return str_ptr - 1;
}
```