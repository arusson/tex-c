# Section 444

```c << Scan a numeric constant >>=
radix = 10;
m = 214748364;
if (cur_tok == OCTAL_TOKEN) {
    radix = 8;
    m = 0x10000000;
    get_x_token();
}
else if (cur_tok == HEX_TOKEN) {
    radix = 16;
    m = 0x8000000;
    get_x_token();
}
vacuous = true;
cur_val = 0;
// << Accumulate the constant until |cur_tok| is not a suitable digit >>
if (vacuous) {
    // << Express astonishment that no number was here >>
}
else if (cur_cmd != SPACER) {
    back_input();
}
```
