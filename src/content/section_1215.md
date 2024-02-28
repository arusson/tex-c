# Section 1215

When a control sequence is to be defined, by `\def` or `\let` or something similar, the *get_r_token* routine will substitute a special control sequence for a token that is not redefinable.

```c << Declare subprocedures for |prefixed_command| >>=
void get_r_token() {
restart:
    do {
        get_token();
    } while (cur_tok == SPACE_TOKEN);
    if (cur_cs == 0 || cur_cs > FROZEN_CONTROL_SEQUENCE) {
        print_err("Missing control sequence inserted");
        help5("Please don't say `\\def cs{...}', say `\\def\\cs{...}'.")
            ("I've inserted an inaccessible control sequence so that your")
            ("definition will be completed without mixing me up too badly.")
            ("You can recover graciously from this error, if you're")
            ("careful; see exercise 27.2 in The TeXbook.");
        if (cur_cs == 0) {
            back_input();
        }
        cur_tok = CS_TOKEN_FLAG + FROZEN_PROTECTION;
        ins_error();
        goto restart;
    }
}
```
