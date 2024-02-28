# Section 598

To put a byte in the buffer without paying the cost of invoking a procedure
each time, we use the macro *dvi_out*.

```c include/dvi.h
#define dvi_out(X)                  \
    do {                            \
        dvi_buf[dvi_ptr] = (X);     \
        incr(dvi_ptr);              \
        if (dvi_ptr == dvi_limit) { \
            dvi_swap();             \
        }                           \
    } while (0)
```

```c dvi.c
// outputs half of the buffer
void dvi_swap() {
    if (dvi_limit == DVI_BUF_SIZE) {
        write_dvi(0, half_buf - 1);
        dvi_limit = half_buf;
        dvi_offset += DVI_BUF_SIZE;
        dvi_ptr = 0;
    }
    else {
        write_dvi(half_buf, DVI_BUF_SIZE - 1);
        dvi_limit = DVI_BUF_SIZE;
    }
    dvi_gone += half_buf;
}
```
