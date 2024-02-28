# Section 365

No new control sequences will be defined except during a call of *get_token*, or when `\csname` compresses a token list, because *no_new_control_sequence* is always *true* at other times.

```c parser/get_next_token.c
// sets |cur_cmd|, |cur_chr|, |cur_tok|
void get_token() {
    no_new_control_sequence = false;
    get_next();
    no_new_control_sequence = true;
    if (cur_cs == 0) {
        cur_tok = (cur_cmd * 256) + cur_chr;
    }
    else {
        cur_tok = CS_TOKEN_FLAG + cur_cs;
    }
}
```
