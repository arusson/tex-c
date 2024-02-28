# Section 506

An active character will be treated as category 13 following `\if\noexpand` or following `\ifcat\noexpand`.
We use the fact that active characters have the smallest tokens, among all control sequences.

```c include/parser.h
#define get_x_token_or_active_char                           \
    do {                                                     \
        get_x_token();                                       \
        if (cur_cmd == RELAX && cur_chr == NO_EXPAND_FLAG) { \
            cur_cmd = ACTIVE_CHAR;                           \
            cur_chr = cur_tok - CS_TOKEN_FLAG - ACTIVE_BASE; \
        }                                                    \
    } while (0)
```

```c << Test if two characters match >>=
get_x_token_or_active_char;
if (cur_cmd > ACTIVE_CHAR ||cur_chr > 255) {
    // not a character
    m = RELAX;
    n = 256;
}
else {
    m = cur_cmd;
    n = cur_chr;
}
get_x_token_or_active_char;
if (cur_cmd > ACTIVE_CHAR || cur_chr > 255) {
    cur_cmd = RELAX;
    cur_chr = 256;
}
if (this_if == IF_CHAR_CODE) {
    b = (n == cur_chr);
}
else {
    b = (m == cur_cmd);
}
```
