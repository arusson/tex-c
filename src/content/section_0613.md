# Section 613

```c << Change buffered instruction to |y| or |w| and |goto found| >>=
k = location(p) - dvi_offset;
if (k < 0) {
    k += DVI_BUF_SIZE;
}
dvi_buf[k] += Y1 - DOWN1;
info(p) = Y_HERE;
goto found;
```
