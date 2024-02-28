# Section 426

```c << Fetch a font integer >>=
scan_font_ident();
if (m == 0) {
    scanned_result(hyphen_char[cur_val], INT_VAL);
}
else {
    scanned_result(skew_char[cur_val], INT_VAL);
}
```
