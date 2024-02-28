# Section 1269

```c << Insert a token saved by \afterassignment, if any >>=
if (after_token != 0) {
    cur_tok = after_token;
    back_input();
    after_token = 0;
}
```
