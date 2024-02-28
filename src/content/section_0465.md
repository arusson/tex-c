# Section 465

The main reason for wanting *str_toks* is the next function, *the_toks*, which has similar input/output characteristics.

This procedure is supposed to scan something like '`\skip\count12`', i.e., whatever can follow '`\the`', and it constructs a token list containing something like '`-3.0pt minus 0.5fill`'.

```c parser/build_tokens.c
pointer the_toks() {
    int  old_setting; // holds |selector| setting
    pointer p, q, r; // used for copying a token list
    pool_pointer b;  // base of temporary string
    get_x_token();
    scan_something_internal(TOK_VAL, false);
    if (cur_val_level >= IDENT_VAL) {
        // << Copy the token list >>
    }
    else {
        old_setting = selector;
        selector = NEW_STRING;
        b = pool_ptr;
        switch (cur_val_level) {
        case INT_VAL:
            print_int(cur_val);
            break;
        
        case DIMEN_VAL:
            print_scaled(cur_val);
            print("pt");
            break;
        
        case GLUE_VAL:
            print_spec(cur_val, "pt");
            delete_glue_ref(cur_val);
            break;
        
        case MU_VAL:
            print_spec(cur_val, "mu");
            delete_glue_ref(cur_val);
        } // there are no other cases
        selector = old_setting;
        return str_toks(b);
    }
}
```
