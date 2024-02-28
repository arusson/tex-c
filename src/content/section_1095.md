# Section 1095

```c builder/boxes_and_lists.c
void head_for_vmode() {
    if (mode < 0) {
        if (cur_cmd != HRULE) {
            off_save();
        }
        else {
            print_err("You can't use `");
            print_esc("hrule");
            print("' here except with leaders");
            help2("To put a horizontal rule in an hbox or an alignment,")
                ("you should use \\leaders or \\hrulefill (see The TeXbook).");
            error();
        }
    }
    else {
        back_input();
        cur_tok = par_token;
        back_input();
        token_type = INSERTED;
    }
}
```
