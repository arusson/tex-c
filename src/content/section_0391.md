# Section 391

At this point, the reader will find it advisable to review the explanation of token list format that was presented earlier, since many aspects of that format are of importance chiefly in the *macro_call* routine.

The token list might begin with a string of compulsory tokens before the first *MATCH* or *END_MATCH*.
In that case the macro name is supposed to be followed by those tokens; the following program will set *s = null* to represent this restriction.
Otherwise *s* will be set to the first token of a string that will delimit the next parameter.

```c << Scan the parameters and make |link(r)| point to the macro body; but |return| if an illegal \par is detected >>=
scanner_status = MATCHING;
unbalance = 0;
long_state = eq_type(cur_cs);
if (long_state >= OUTER_CALL) {
    long_state -= 2;
}
do {
    link(TEMP_HEAD) = null;
    if (info(r) > MATCH_TOKEN + 255 || info(r) < MATCH_TOKEN) {
        s = null;
    }
    else {
        match_chr = info(r) - MATCH_TOKEN;
        s = link(r);
        r = s;
        p = TEMP_HEAD;
        m = 0;
    }
    // << Scan a parameter until its delimiter string has been found; or, if |s = null|, simply scan the delimiter string >>
    // now |info(r)| is a token whose command code is either |match| or |end_match|
} while (info(r) != END_MATCH_TOKEN);
```
