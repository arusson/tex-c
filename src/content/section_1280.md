# Section 1280

```c << Print string |s| on the terminal >>=
if (term_offset + length(s) > MAX_PRINT_LINE - 2) {
    print_ln();
}
else if (term_offset > 0 || file_offset > 0 ) {
    print_char(' ');
}
slow_print(s);
update_terminal;
```
