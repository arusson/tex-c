# Section 357

Let's consider now what happens when *get_next* is looking at a token list.

```c << Input from token list, |goto restart| if end of list or if a parameter needs to be expanded >>=
if (loc != null) {
    // list not exhausted
    t = info(loc);
    loc = link(loc); // move to next
    if (t >= CS_TOKEN_FLAG) {
        // a control sequence token
        cur_cs = t - CS_TOKEN_FLAG;
        cur_cmd = eq_type(cur_cs);
        cur_chr = equiv(cur_cs);
        if (cur_cmd >= OUTER_CALL) {
            if (cur_cmd == DONT_EXPAND) {
                // << Get the next token, suppressing expansion >>
            }
            else {
                check_outer_validity();
            }
        }
    }
    else {
        cur_cmd = t / 256;
        cur_chr = t % 256;
        switch (cur_cmd) {
        case LEFT_BRACE:
            incr(align_state);
            break;
        
        case RIGHT_BRACE:
            decr(align_state);
            break;
        
        case OUT_PARAM:
            // << Insert macro parameter and |goto restart| >>
        
        default:
            do_nothing;
        }
    }
}
else {
    // we are done with this token list
    end_token_list();
    goto restart; // resume previous level
}
```
