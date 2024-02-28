# Section 379

Sometimes the expansion looks too far ahead, so we want to insert a harmless `\relax` into the user's input.

```c parser/expand_next_token.c
void insert_relax() {
    cur_tok = CS_TOKEN_FLAG + cur_cs;
    back_input();
    cur_tok = CS_TOKEN_FLAG + FROZEN_RELAX;
    back_input();
    token_type = INSERTED;
}
```
