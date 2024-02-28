# Section 518

Conversely, here is a routine that takes three strings and prints a file name that might have produced them.
(The routine is system dependent, because some operating systems put the file area last instead of first.)

```c io/basic_printing.c
void print_file_name(int n, int a, int e) {
    slow_print(a);
    slow_print(n);
    slow_print(e);
}
```
