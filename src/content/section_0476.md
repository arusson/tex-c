# Section 476

```c << If the next character is a parameter number, make |cur_tok| a |MATCH| token; but if it is a left brace; store '|LEFT_BRACE|, |END_MATCH|', set |hash_brace|, and |goto done| >>=
s = MATCH_TOKEN + cur_chr;
get_token();
if (cur_tok < LEFT_BRACE_LIMIT) {
    hash_brace = cur_tok;
    store_new_token(cur_tok);
    store_new_token(END_MATCH_TOKEN);
    goto done;
}
if (t == ZERO_TOKEN + 9) {
    print_err("You already have nine parameters");
    help2("I'm going to ignore the # sign you just used,")
        ("as well as the token that followed it.");
    error();
    continue;
}
else {
    incr(t);
    if (cur_tok != t) {
        print_err("Parameters must be numbered consecutively");
        help2("I've inserted the digit you should have used after the #.")
            ("Type `1' to delete what you did use.");
        back_error();
    }
    cur_tok = s;
}
```
