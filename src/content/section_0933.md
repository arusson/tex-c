# Section 933

```c << Search |hyph_list| for pointers to |p| >>=
for(q = 0; q <= HYPH_SIZE; q++) {
    if (hyph_list[q] == p) {
        print_nl("HYPH(");
        print_int(q);
        print_char(')');
    }
}
```
