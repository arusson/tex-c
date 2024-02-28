# Section 234

```c << Show the font identifier in |eqtb[n]| >>=
if (n == CUR_FONT_LOC) {
    print("current font");
}
else if (n < MATH_FONT_BASE + 16) {
    print_esc("textfont");
    print_int(n - MATH_FONT_BASE);
}
else if (n < MATH_FONT_BASE + 32) {
    print_esc("scriptfont");
    print_int(n - MATH_FONT_BASE - 16);
}
else  {
    print_esc("scriptscriptfont");
    print_int(n - MATH_FONT_BASE - 32);
}
print_char('=');
print_esc_strnumber(hh_rh(hash[FONT_ID_BASE + equiv(n)])); // that's |font_id_text(equiv(n))|
```
