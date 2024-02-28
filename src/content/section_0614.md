# Section 614

```c << Change buffered instruction to |z| or |x| and |goto found| >>=
k = location(p) - dvi_offset;
if (k < 0) {
    k += DVI_BUF_SIZE;
}
dvi_buf[k] += Z1 - DOWN1;
info(p) = Z_HERE;
goto found;
```
