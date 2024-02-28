# Section 643

```c << Output the font definitions for all fonts that were used >>=
while (font_ptr > FONT_BASE) {
    if (font_used[font_ptr]) {
        dvi_font_def(font_ptr);
    }
    decr(font_ptr);
}
```
