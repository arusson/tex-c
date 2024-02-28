# Section 962

```c << Append a new letter or a hyphen level >>=
if (digit_sensed || cur_chr < '0' || cur_chr > '9') {
    if (cur_chr == '.') {
        cur_chr = 0; // edge-of-word delimiter
    }
    else {
        cur_chr = lc_code(cur_chr);
        if (cur_chr == 0) {
            print_err("Nonletter");
            help1("(See Appendix H.)");
            error();
        }
    }
    if (k < 63) {
        incr(k);
        hc[k] = cur_chr;
        hyf[k] = 0;
        digit_sensed = false;
    }
}
else if (k < 63) {
    hyf[k] = cur_chr - '0';
    digit_sensed = true;
}
```
