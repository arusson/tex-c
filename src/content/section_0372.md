# Section 372

```c << Manufacture a control sequence name >>=
r = get_avail();
p = r; // head of the list of characters
do {
    get_x_token();
    if (cur_cs == 0) {
        store_new_token(cur_tok);
    }
} while (cur_cs == 0);
if (cur_cmd != END_CS_NAME) {
    // << Complain about missing \endcsname >>
}
// << Look up the characters of list |r| in the hash table, and set |cur_cs| >>
flush_list(r);
if (eq_type(cur_cs) == UNDEFINED_CS) {
    eq_define(cur_cs, RELAX, 256); // N.B.: The |save_stack| might change
} // the control sequence will now match '\relax'
cur_tok = cur_cs + CS_TOKEN_FLAG;
back_input();
```
