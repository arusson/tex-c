# Section 392

If *info(r)* is a *MATCH* or *END_MATCH* command, it cannot be equal to any token found by *get_token*.
Therefore an undelimited parameter---i.e., a *MATCH* that is immediately followed by *MATCH* or *END_MATCH*---will always fail the test *'cur_tok = info(r)'* in the following algorithm.

```c << Scan a parameter until its delimiter string has been found; or, if |s = null|, simply scan the delimiter string >>=
continue_lbl:
get_token(); // set |cur_tok| to the next token of input
if (cur_tok == info(r)) {
    // << Advance |r|; |goto found| if the parameter delimiter has been fully matched, otherwise |goto continue_lbl| >>
}
// << Contribute the recently matched tokens to the current parameter, and |goto continue| if a partial match is still in effect; but abort if |s = null| >>
if (cur_tok == par_token && long_state != LONG_CALL) {
    // << Report a runaway argument and abort >>
}
if (cur_tok < RIGHT_BRACE_LIMIT) {
    if (cur_tok < LEFT_BRACE_LIMIT) {
        // << Contribute an entire group to the current parameter >>
    }
    else {
        // << Report an extra right brace and |goto continue| >>
    }
}
else {
    // << Store the current token, but |goto continue_lbl| if it is a blank space that would become an undelimited parameter >>
}
incr(m);
if (info(r) > END_MATCH_TOKEN || info(r) < MATCH_TOKEN) {
    goto continue_lbl;
}
found:
if (s != null) {
    // << Tidy up the parameter just scanned, and tuck it away >>
}
```
