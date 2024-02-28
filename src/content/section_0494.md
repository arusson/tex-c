# Section 494

Here is a procedure that ignores text until coming to an `\or`, `\else`, or `\fi` at the current level of `\if ... \fi` nesting.
After it has acted, *cur_chr* will indicate the token that was found, but *cur_tok* will not be set (because this makes the procedure run faster).

```c parser/conditional.c
// << Start file |conditional.c| >>

void pass_text() {
    int l; // level of \if ... \fi nesting
    small_number save_scanner_status; // |scanner_status| upon entry
    save_scanner_status = scanner_status;
    scanner_status = SKIPPING;
    l = 0;
    skip_line = line;
    while(true) {
        get_next();
        if (cur_cmd == FI_OR_ELSE) {
            if (l == 0) {
                break; // Goto done
            }
            if (cur_chr == FI_CODE) {
                decr(l);
            }
        }
        else if (cur_cmd == IF_TEST) {
            incr(l);
        }
    }
    // done:
    scanner_status = save_scanner_status;
}
```
