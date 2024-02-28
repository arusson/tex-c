# Section 418

```c << Fetch the |space_factor| or the |prev_depth| >>=
if (abs(mode) != m) {
    print_err("Improper ");
    print_cmd_chr(SET_AUX, m);
    help4("You can refer to \\spacefactor only in horizontal mode;")
        ("you can refer to \\prevdepth only in vertical mode; and")
        ("neither of these is meaningful inside \\write. So")
        ("I'm forgetting what you said and using zero instead.");
    error();
    if (level != TOK_VAL) {
        scanned_result(0, DIMEN_VAL);
    }
    else {
        scanned_result(0, INT_VAL);
    }
}
else if (m == VMODE) {
    scanned_result(prev_depth, DIMEN_VAL);
}
else {
    scanned_result(space_factor, INT_VAL);
}
```
