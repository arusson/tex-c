# Section 381

The *get_x_token* procedure is essentially equivalent to two consecutive procedure calls: *get_next*, *x_token*.

```c parser/expand_next_token.c
// |get_x_token| without the initial |get_next|
void x_token() {
    while (cur_cmd > MAX_COMMAND) {
        expand();
        get_next();
    }
    if (cur_cs == 0) {
        cur_tok = (cur_cmd * 256) + cur_chr;
    }
    else {
        cur_tok = CS_TOKEN_FLAG + cur_cs;
    }
}
```
