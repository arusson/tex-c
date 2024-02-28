# Section 193

```c << Display ligature |p| >>=
print_font_and_char(lig_char(p));
print(" (ligature ");
if (subtype(p) > 1) {
    print_char('|');
}
font_in_short_display = font(lig_char(p));
short_display(lig_ptr(p));
if (odd(subtype(p))) {
    print_char('|');
}
print_char(')');
```
