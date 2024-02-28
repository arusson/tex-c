# Section 621

```c << Change font |dvi_f| to |f| >>=
if (!font_used[f]) {
    dvi_font_def(f);
    font_used[f] = true;
}
if (f <= 64 + FONT_BASE) {
    dvi_out(f - FONT_BASE - 1 + FNT_NUM_0);
}
else {
    dvi_out(FNT1);
    dvi_out(f - FONT_BASE - 1);
}
dvi_f = f;
```
