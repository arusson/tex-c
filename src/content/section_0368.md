# Section 368

It takes only a little shuffling to do what $\TeX$ calls `\expandafter`.

```c << Expand the token after the next token >>=
get_token();
t = cur_tok;
get_token();
if (cur_cmd > MAX_COMMAND) {
    expand();
}
else {
    back_input();
}
cur_tok = t;
back_input();
```
