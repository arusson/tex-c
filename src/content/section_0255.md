# Section 255

When the debugging routine *search_mem* is looking for pointers having a given value, it is interested only in regions 1 to&nbsp;3 of *eqtb*, and in the first part of region&nbsp;4.

```c << Search |eqtb| for equivalents equal to |p| >>=
for(q = ACTIVE_BASE; q <= BOX_BASE + 255; q++) {
    if (equiv(q) == p) {
        print_nl("EQUIV(");
        print_int(q);
        print_char(')');
    }
}
```
