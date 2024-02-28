# Section 478

Here we insert an entire token list created by *the_toks* without expanding it further.

```c << Expand the next part of the input >>=
while(true) {
    get_next();
    if (cur_cmd <= MAX_COMMAND) {
        break; // Goto done2
    }
    if (cur_cmd != THE) {
        expand();
    }
    else {
        q = the_toks();
        if (link(TEMP_HEAD) != null) {
            link(p) = link(TEMP_HEAD);
            p = q;
        }
    }
}
// done2:
x_token();
```
