# Section 1350

The next subroutine uses *cur_chr* to decide what sort of whatsit is involved, and also inserts a *write_stream* number.

```c << Declare procedures needed in |do_extension| >>+=
void new_write_whatsit(small_number w) {
    new_whatsit(cur_chr, w);
    if (w != WRITE_NODE_SIZE) {
        scan_four_bit_int();
    }
    else {
        scan_int();
        if (cur_val < 0) {
            cur_val = 17;
        }
        else if (cur_val > 15) {
            cur_val = 16;
        }
    }
    write_stream(tail) = cur_val;
}
```
