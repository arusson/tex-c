# Section 94

Here is the most dreaded error message.

```c error.c
// stop due to finiteness
void overflow(char *s, int n) {
    normalize_selector();
    print_err("TeX capacity exceeded, sorry [");
    print(s);
    print_char('=');
    print_int(n);
    print_char(']');
    help2("If you really absolutely need more capacity,")
        ("you can ask a wizard to enlarge me.");
    succumb();
}
```
