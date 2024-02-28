# Section 61

Here is the very first thing that $\TeX$ prints: a headline that identifies the version number and format package.
The *term_offset* variable is temporarily incorrect, but the discrepancy is not serious since we assume that this part of the program is system dependent.

```c << Initialize the output routines >>+=
wterm(BANNER);
if (format_ident == 0) {
    wterm_ln(" (no format preloaded)");
}
else {
    slow_print(format_ident);
    print_ln();
}
update_terminal;
```
