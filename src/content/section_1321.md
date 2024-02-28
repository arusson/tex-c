# Section 1321

```c << Undump the font information >>=
undump_size(7, FONT_MEM_SIZE, "font mem size", fmem_ptr);
for(k = 0; k <= fmem_ptr - 1; k++) {
    undump_wd(font_info[k]);
}
undump_size(FONT_BASE, FONT_MAX, "font max", font_ptr);
for(k = NULL_FONT; k <= font_ptr; k++) {
    // << Undump the array info for internal font number |k| >>
}
```
