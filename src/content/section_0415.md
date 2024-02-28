# Section 415

```c << Fetch a token list or font identifier, provided that |level = TOK_VAL| >>=
if (level != TOK_VAL) {
    print_err("Missing number, treated as zero");
    help3("A number should have been here; I inserted `0'.")
        ("(If you can't figure out why I needed to see a number,")
        ("look up `weird error' in the index to The TeXbook.)");
    back_error();
    scanned_result(0, DIMEN_VAL);
}
else if (cur_cmd <= ASSIGN_TOKS) {
    if (cur_cmd < ASSIGN_TOKS) {
        // |cur_cmd == TOKS_REGISTER|
        scan_eight_bit_int();
        m = TOKS_BASE + cur_val;
    }
    scanned_result(equiv(m), TOK_VAL);
}
else {
    back_input();
    scan_font_ident();
    scanned_result(FONT_ID_BASE + cur_val, IDENT_VAL);
}
```
