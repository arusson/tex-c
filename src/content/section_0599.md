# Section 599

Here is how we clean out the buffer when $\TeX$ is all through; *dvi_ptr* will be a multiple of&nbsp;4.

```c << Empty the last bytes out of |dvi_buf| >>=
if (dvi_limit == half_buf) {
    write_dvi(half_buf, DVI_BUF_SIZE - 1);
}
if (dvi_ptr > 0) {
    write_dvi(0, dvi_ptr - 1);
}
```
