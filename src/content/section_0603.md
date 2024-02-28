# Section 603

```c << Output the font name whose internal number is |f| >>=
for(k = str_start[font_area[f]]; k < str_start[font_area[f] + 1]; k++) {
    dvi_out(str_pool[k]);
}
for(k = str_start[font_name[f]]; k < str_start[font_name[f] + 1]; k++) {
    dvi_out(str_pool[k]);
}
```
