# Section 474

```c << Scan and build the parameter part of the macro definition >>=
while(true) {
    get_token(); // set |cur_cmd|, |cur_chr|, |cur_tok|
    if (cur_tok < RIGHT_BRACE_LIMIT) {
        break; // Goto done1
    }
    if (cur_cmd == MAC_PARAM) {
        // << If the next character is a parameter number, make |cur_tok| a |MATCH| token; but if it is a left brace; store '|LEFT_BRACE|, |END_MATCH|', set |hash_brace|, and |goto done| >>
    }
    store_new_token(cur_tok);
}
// done1:
store_new_token(END_MATCH_TOKEN);
if (cur_cmd == RIGHT_BRACE) {
    // << Express shock at the missing left brace; |goto found| >>
}
done:
```
