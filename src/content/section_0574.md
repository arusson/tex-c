# Section 574

```c << Read extensible character recipes >>=
for(k = exten_base[f]; k <= param_base[f] - 1; k++) {
    store_four_quarters(font_info[k]);
    if (a != 0) {
        check_existence(a);
    }
    if (b != 0) {
        check_existence(b);
    }
    if (c != 0) {
        check_existence(c);
    }
    check_existence(d);
}
```
