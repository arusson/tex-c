# Section 1099

```c builder/boxes_and_lists.c
void begin_insert_or_adjust() {
    if (cur_cmd == VADJUST) {
        cur_val = 255;
    }
    else {
        scan_eight_bit_int();
        if (cur_val == 255) {
            print_err("You can't ");
            print_esc("insert");
            print_int(255);
            help1("I'm changing to \\insert0; box 255 is special.");
            error();
            cur_val = 0;
        }
    }
    saved(0) = cur_val;
    incr(save_ptr);
    new_save_level(INSERT_GROUP);
    scan_left_brace();
    normal_paragraph();
    push_nest();
    mode = -VMODE;
    prev_depth = IGNORE_DEPTH;
}
```
