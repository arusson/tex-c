# Section 1117

The space factor does not change when we append a discretionary node, but it starts out as 1000 in the subsidiary lists.

```c builder/boxes_and_lists.c
void append_discretionary() {
    int c; // hyphen character
    tail_append(new_disc());
    if (cur_chr == 1) {
        c = hyphen_char[cur_font];
        if (c >= 0 && c < 256) {
            pre_break(tail) = new_character(cur_font, c);
        }
    }
    else {
        incr(save_ptr);
        saved(-1) = 0;
        new_save_level(DISC_GROUP);
        scan_left_brace();
        push_nest();
        mode = -HMODE;
        space_factor = 1000;
    }
}
```
