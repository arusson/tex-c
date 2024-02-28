# Section 48

```c include/strings.h
#define app_lc_hex(X)                  \
    do {                               \
        l = (X);                       \
        if (l < 10) {                  \
            append_char(l + '0');      \
        }                              \
        else {                         \
            append_char(l - 10 + 'a'); \
        }                              \
    } while (0)
```

```c << Make the first 256 strings >>=
for (k = 0; k < 256; k++) {
    if (k < ' ' || k > '~') {
        append_char('^');
        append_char('^');
        if (k < 64) {
            append_char(k + 64);
        }
        else if (k < 128) {
            append_char(k - 64);
        }
        else {
            app_lc_hex(k / 16);
            app_lc_hex(k % 16);
        }
    }
    else {
        append_char(k);
    }
    make_string();
}
```
