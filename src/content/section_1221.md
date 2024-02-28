# Section 1221

```c << Assignments >>+=
case LET:
    n = cur_chr;
    get_r_token();
    p = cur_cs;
    if (n == NORMAL) {
        do {
            get_token();
        } while (cur_cmd == SPACER);
        if (cur_tok == OTHER_TOKEN + '=') {
            get_token();
            if (cur_cmd == SPACER) {
                get_token();
            }
        }
    }
    else {
        get_token();
        q = cur_tok;
        get_token();
        back_input();
        cur_tok = q;
        back_input(); // look ahead, then back up
    } // note that |back_input| doesn't affect |cur_cmd|, |cur_chr|
    if (cur_cmd >= CALL) {
        add_token_ref(cur_chr);
    }
    define(p, cur_cmd, cur_chr);
    break;
```
