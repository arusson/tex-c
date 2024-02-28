# Section 479

```c << Look for parameter number or ## >>=
s = cur_tok;
if (xpand) {
    get_x_token();
}
else {
    get_token();
}
if (cur_cmd != MAC_PARAM) {
    if (cur_tok <= ZERO_TOKEN || cur_tok > t) {
        print_err("Illegal parameter number in definition of ");
        sprint_cs(warning_index);
        help3("You meant to type ## instead of #, right?")
            ("Or maybe a } was forgotten somewhere earlier, and things")
            ("are all screwed up? I'm going to assume that you meant ##.");
        back_error();
        cur_tok = s;
    }
    else {
        cur_tok = OUT_PARAM_TOKEN - '0' + cur_chr;
    }
}
```
