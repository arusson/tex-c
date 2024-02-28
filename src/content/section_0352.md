# Section 352

Notice that a code like `^^8` becomes `x` if not followed by a hex digit.

```c include/parser.h
#define is_hex(X) (((X) >= '0' && (X) <= '9' ) || ((X) >= 'a' && (X) <= 'f'))
#define hex_to_cur_chr                            \
    do {                                          \
        if (c <= '9') {                           \
            cur_chr = c - '0';                    \
        }                                         \
        else {                                    \
            cur_chr = c - 'a' + 10;               \
        }                                         \
        if (cc <= '9') {                          \
            cur_chr = 16*cur_chr + cc - '0';      \
        }                                         \
        else {                                    \
            cur_chr = 16*cur_chr + cc - 'a' + 10; \
        }                                         \
    } while (0)
```

```c << If this |SUP_MARK| starts an expanded character like ^^A or ^^df, then |goto reswitch|, otherwise set |state = MID_LINE| >>=
if (cur_chr == buffer[loc] && loc < limit) {
    c = buffer[loc + 1];
    if (c < 128) {
        // yes we have an expanded char
        loc += 2;
        if (is_hex(c) && loc <= limit) {
            cc = buffer[loc];
            if (is_hex(cc)) {
                incr(loc);
                hex_to_cur_chr;
                goto reswitch;
            }
        }
        if (c < 64) {
            cur_chr = c + 64;
        }
        else {
            cur_chr = c - 64;
        }
        goto reswitch;
    }
}
state = MID_LINE;
```
