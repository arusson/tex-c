# Section 1227

```c << If the right-hand side is a token parameter or token register, finish the assignment and |goto done| >>=
if (cur_cmd == TOKS_REGISTER) {
    scan_eight_bit_int();
    cur_cmd = ASSIGN_TOKS;
    cur_chr = TOKS_BASE + cur_val;
}
if (cur_cmd == ASSIGN_TOKS) {
    q = equiv(cur_chr);
    if (q == null) {
        define(p, UNDEFINED_CS, null);
    }
    else {
        add_token_ref(q);
        define(p, CALL, q);
    }
    goto done;
}
```
