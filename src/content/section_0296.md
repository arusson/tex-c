# Section 296

The *print_meaning* subroutine displays *cur_cmd* and *cur_chr* in symbolic form, including the expansion of a macro or mark.

```c io/display_tokens.c
void print_meaning() {
    print_cmd_chr(cur_cmd, cur_chr);
    if (cur_cmd >= CALL) {
        print_char(':');
        print_ln();
        token_show(cur_chr);
    }
    else if (cur_cmd == TOP_BOT_MARK) {
        print_char(':');
        print_ln();
        token_show(cur_mark[cur_chr]);
    }
}
```
