# Section 91

A dozen or so error messages end with a parenthesized integer, so we save a teeny bit of program space by declaring the following procedure:

```c error.c
void int_error(int n) {
    print(" (");
    print_int(n);
    print_char(')');
    error();
}
```
