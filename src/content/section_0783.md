# Section 783

Spaces are eliminated from the beginning of a template.

```c << Scan the template <u_j>, putting the resulting token list in |HOLD_HEAD| >>=
p = HOLD_HEAD;
link(p) = null;
while(true) {
    get_preamble_token();
    if (cur_cmd == MAC_PARAM) {
        break; // goto done1
    }
    if (cur_cmd <= CAR_RET
        && cur_cmd >= TAB_MARK
        && align_state == -1000000)
    {
        if (p == HOLD_HEAD
            && cur_loop == null
            && cur_cmd == TAB_MARK)
        {
            cur_loop = cur_align;
        }
        else {
            print_err("Missing # inserted in alignment preamble");
            help3("There should be exactly one # between &'s, when an")
                ("\\halign or \\valign is being set up. In this case you had")
                ("none, so I've put one in; maybe that will work.");
            back_error();
            break; // goto done1
        }
    }
    else if (cur_cmd != SPACER || p != HOLD_HEAD) {
        link(p) = get_avail();
        p = link(p);
        info(p) = cur_tok;
    }
}
// done1:
```
