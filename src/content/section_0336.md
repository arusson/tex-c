# Section 336

Before getting into *get_next*, let's consider the subroutine that is called when an '`\outer`' control sequence has been scanned or when the end of a file has been reached.
These two cases are distinguished by *cur_cs*, which is zero at the end of a file.

```c parser/get_next_token.c
// << Start file |get_next_token.c| >>

void check_outer_validity() {
    pointer p; // points to inserted token list
    pointer q; // auxiliary pointer
    if (scanner_status != NORMAL) {
        deletions_allowed = false;
        // << Back up an outer control sequence so that it can be reread >>
        if (scanner_status > SKIPPING) {
            // << Tell the user what has run away and try to recover >>
        }
        else {
            print_err("Incomplete ");
            print_cmd_chr(IF_TEST, cur_if);
            print("; all text was ignored after line ");
            print_int(skip_line);
            help3("A forbidden control sequence occurred in skipped text.")
                ("This kind of error happens when you say `\\if...' and forget")
                ("the matching `\\fi'. I've inserted a `\\fi'; this might work.");
            if (cur_cs != 0) {
                cur_cs = 0;
            }
            else {
                help_line[2] = "The file ended while I was skipping conditional text.";
            }
            cur_tok = CS_TOKEN_FLAG + FROZEN_FI;
            ins_error();
        }
        deletions_allowed = true;
    }
}
```
