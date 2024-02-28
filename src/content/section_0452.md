# Section 452

 When the following code is executed, we have *cur_tok = POINT_TOKEN*, but this token has been backed up using *back_input*; we must first discard it.

It turns out that a decimal point all by itself is equivalent to '`0.0`'.
Let's hope people don't use that fact.

```c << Scan decimal fraction >>=
k = 0;
p = null;
get_token(); // |POINT_TOKEN| is being re-scanned
while(true) {
    get_x_token();
    if (cur_tok > ZERO_TOKEN + 9 || cur_tok < ZERO_TOKEN) {
        break; // Goto done1
    }
    if (k < 17) {
        // digits for |k >= 17| cannot affect the result
        q = get_avail();
        link(q) = p;
        info(q) = cur_tok - ZERO_TOKEN;
        p = q;
        incr(k);
    }
}
// done1:
for(kk = k; kk >= 1; kk--) {
    dig[kk - 1] = info(p);
    q = p;
    p = link(p);
    free_avail(q);
}
f = round_decimals(k);
if (cur_cmd != SPACER) {
    back_input();
}
```
