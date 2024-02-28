# Section 937

```c << Append a new letter or hyphen >>=
if (cur_chr == '-') {
    // << Append the value |n| to list |p| >>
}
else {
    if (lc_code(cur_chr) == 0) {
        print_err("Not a letter");
        help2("Letters in \\hyphenation words must have \\lccode>0.")
            ("Proceed; I'll ignore the character I just read.");
        error();
    }
    else if (n < 63) {
        incr(n);
        hc[n] = lc_code(cur_chr);
    }
}
```
