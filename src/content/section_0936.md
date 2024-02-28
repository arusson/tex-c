# Section 936

```c << Give improper \hyphenation error >>=
print_err("Improper ");
print_esc("hyphenation");
print(" will be flushed");
help2("Hyphenation exceptions must contain only letters")
    ("and hyphens. But continue; I'll forgive and forget.");
error();
```
