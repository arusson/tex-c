# Section 62

The procedure *print_nl* is like *print*, but it makes sure that the string appears at the beginning of a new line.

> ![NOTE]
> Same as *print*, there are two versions.

```c io/basic_printing.c
void print_nl(char *s) {
    if ((term_offset > 0 && odd(selector))
        || (file_offset > 0 && selector >= LOG_ONLY))
    {
        print_ln();
    }
    print(s);
}

// prints string |s| at beginning of line
void print_nl_strnumber(str_number s) {
    if ((term_offset > 0 && odd(selector))
        || (file_offset > 0 && selector >= LOG_ONLY))
    {
        print_ln();
    }
    print_strnumber(s);
}
```
