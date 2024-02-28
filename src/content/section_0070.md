# Section 70

The *print* subroutine will not print a string that is still being created.
The following procedure will.

```c io/basic_printing.c
// prints a yet-unmade string
void print_current_string() {
    pool_pointer j; // points to current character code
    j = str_start[str_ptr];
    while (j < pool_ptr) {
        print_char(str_pool[j]);
        incr(j);
    }
}
```
