# Section 355

 Whenever we reach the following piece of code, we will have *cur_chr = buffer[k − 1]* and *k* $\leq$ *limit + 1* and *cat = cat_code(cur_chr)*.
If an expanded code like `^^A` or `^^df` appears in *buffer[(k − 1) .. (k + 1)]* or *buffer[(k − 1) .. (k + 2)]*, we will store the corresponding code in *buffer[k − 1]* and shift the rest of the buffer left two or three places.

```c << If an expanded code is present, reduce it and |goto start_cs| >>=
if (buffer[k] == cur_chr
    && cat == SUP_MARK
    && k < limit)
{
    c = buffer[k + 1];
    if (c < 128) {
         // yes, one is indeed present
        d = 2;
        if (is_hex(c) && k + 2 <= limit) {
            cc = buffer[k + 2];
            if (is_hex(cc)) {
                incr(d);
            }
        }
        if (d > 2) {
            hex_to_cur_chr;
            buffer[k - 1] = cur_chr;
        }
        else if (c < 64) {
            buffer[k - 1] = c + 64;
        }
        else {
            buffer[k - 1] = c - 64;
        }
        limit -= d;
        first -= d;
        while (k <= limit) {
            buffer[k] = buffer[k + d];
            incr(k);
        }
        goto start_cs;
    }
}
```
