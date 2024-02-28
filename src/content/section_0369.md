# Section 369

The implementation of `\noexpand` is a bit trickier, because it is necessary to insert a special *'DONT_EXPAND'* marker into $\TeX$'s reading mechanism.
This special marker is processed by *get_next*, but it does not slow down the inner loop.

Since `\outer` macros might arise here, we must also clear the *scanner_status* temporarily.

```c << Suppress expansion of the next token >>=
save_scanner_status = scanner_status;
scanner_status = NORMAL;
get_token();
scanner_status = save_scanner_status;
t = cur_tok;
back_input(); // now |start| and |loc| point to the backed-up token |t|
if (t >= CS_TOKEN_FLAG) {
    p = get_avail();
    info(p) = CS_TOKEN_FLAG + FROZEN_DONT_EXPAND;
    link(p) = loc;
    start = p;
    loc = p;
}
```
