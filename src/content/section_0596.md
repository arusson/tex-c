# Section 596

Initially the buffer is all in one piece; we will output half of it only after it first fills up.

```c << Set initial values of key variables >>+=
half_buf = DVI_BUF_SIZE / 2;
dvi_limit = DVI_BUF_SIZE;
dvi_ptr = 0;
dvi_offset = 0;
dvi_gone = 0;
```
