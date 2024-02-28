# Section 784

```c << Scan the template <v_j>, putting the resulting token list in |HOLD_HEAD| >>=
p = HOLD_HEAD;
link(p) = null;
while(true) {
    get_preamble_token();
    if (cur_cmd <= CAR_RET
        && cur_cmd >= TAB_MARK
        && align_state == -1000000)
    {
        break; // goto done2
    }
    if (cur_cmd == MAC_PARAM) {
        print_err("Only one # is allowed per tab");
        help3("There should be exactly one # between &'s, when an")
            ("\\halign or \\valign is being set up. In this case you had")
            ("more than one, so I'm ignoring all but the first.");
        error();
        continue;
    }
    link(p) = get_avail();
    p = link(p);
    info(p) = cur_tok;
}
// done2:
link(p) = get_avail();
p = link(p);
info(p) = END_TEMPLATE_TOKEN; // put \endtemplate at the end
```
