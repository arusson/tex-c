# Section 470

The procedure *conv_toks* uses *str_toks* to insert the token list for *convert* functions into the scanner; '`\outer`' control sequences are allowed to follow '`\string`' and '`\meaning`'.

```c parser/build_tokens.c
void conv_toks() {
    int old_setting; // holds |selector| setting
    int c; // desired type of conversion
    small_number save_scanner_status; // |scanner_status| upon entry
    pool_pointer b; // base of temporary string
    c = cur_chr;
    // << Scan the argument for command |c| >>
    old_setting = selector;
    selector = NEW_STRING;
    b = pool_ptr;
    // << Print the result of command |c| >>
    selector = old_setting;
    link(GARBAGE) = str_toks(b);
    ins_list(link(TEMP_HEAD));
}
```
