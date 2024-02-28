# Section 573

```c include/font_metric.h
#define check_existence(X)                              \
    do {                                                \
        check_byte_range((X));                          \
        qw = char_info(f, (X)); /* N.B.: not |qi(X)| */ \
        if (!char_exists(qw)) {                         \
            abort;                                      \
        }                                               \
    } while (0)
```

```c << Read ligature/kern program >>=
bch_label = 0x7fff;
bchar = 256;
if (nl > 0) {
    for(k = lig_kern_base[f]; k <= kern_base[f] + KERN_BASE_OFFSET - 1; k++) {
        store_four_quarters(font_info[k]);
        if (a > 128) {
            if (256*c + d >= nl) {
                abort;
            }
            if (a == 255 && k == lig_kern_base[f]) {
                bchar = b;
            }
        }
        else {
            if (b != bchar) {
                check_existence(b);
            }
            if (c < 128) {
                check_existence(d); // check ligature
            }
            else if (256*(c - 128) + d >= nk) {
                abort; // check kern
            }
            if (a < 128 && k - lig_kern_base[f] + a + 1 >= nl) {
                abort;
            }
        }
    }
    if (a == 255) {
        bch_label = 256*c + d;
    }
}
for(k = kern_base[f] + KERN_BASE_OFFSET; k <= exten_base[f] - 1; k++) {
    store_scaled(font_info[k].sc);
}
```
