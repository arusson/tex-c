# Section 394

A slightly subtle point arises here:
When the parameter delimiter ends with '`#{`', the token list will have a left brace both before and after the *END_MATCH*.
Only one of these should affect the *align_state*, but both will be scanned, so we must make a correction.

```c << Advance |r|; |goto found| if the parameter delimiter has been fully matched, otherwise |goto continue_lbl| >>=
r = link(r);
if (info(r) >= MATCH_TOKEN && info(r) <= END_MATCH_TOKEN) {
    if (cur_tok < LEFT_BRACE_LIMIT) {
        decr(align_state);
    }
    goto found;
}
else {
    goto continue_lbl;
}
```
