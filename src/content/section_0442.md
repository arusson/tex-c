# Section 442

A space is ignored after an alphabetic character constant, so that such constants behave like numeric ones.

```c << Scan an alphabetic character code into |cur_val| >>=
get_token(); // suppress macro expansion
if (cur_tok < CS_TOKEN_FLAG) {
    cur_val = cur_chr;
    if (cur_cmd <= RIGHT_BRACE) {
        if (cur_cmd == RIGHT_BRACE) {
            incr(align_state);
        }
        else {
            decr(align_state);
        }
    }
}
else if (cur_tok < CS_TOKEN_FLAG + SINGLE_BASE) {
    cur_val = cur_tok - CS_TOKEN_FLAG - ACTIVE_BASE;
}
else {
    cur_val = cur_tok - CS_TOKEN_FLAG - SINGLE_BASE;
}
if (cur_val > 255) {
    print_err("Improper alphabetic constant");
    help2("A one-character control sequence belongs after a ` mark.")
        ("So I'm essentially inserting \\0 here.");
    cur_val = '0';
    back_error();
}
else {
    // << Scan an optional space >>
}
```
