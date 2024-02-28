# Section 1320

```c << Dump the font information >>=
dump_int(fmem_ptr);
for(k = 0; k <= fmem_ptr - 1; k++) {
    dump_wd(font_info[k]);
}
dump_int(font_ptr);
for(k = NULL_FONT; k <= font_ptr; k++) {
    // << Dump the array info for internal font number |k| >>
}
print_ln();
print_int(fmem_ptr - 7);
print(" words of font info for ");
print_int(font_ptr - FONT_BASE);
print(" preloaded font");
if (font_ptr != FONT_BASE + 1) {
    print_char('s');
}
```
