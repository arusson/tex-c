# Section 1091

```c builder/boxes_and_lists.c
small_number norm_min(int h) {
    if (h <= 0) {
        return 1;
    }
    if (h >= 63) {
        return 63;
    }
    return h;
}

void new_graf(bool indented) {
    prev_graf = 0;
    if (mode == VMODE || head != tail) {
        tail_append(new_param_glue(PAR_SKIP_CODE));
    }
    push_nest();
    mode = HMODE;
    space_factor = 1000;
    set_cur_lang;
    clang = cur_lang;
    prev_graf = (norm_min(left_hyphen_min)*64 + norm_min(right_hyphen_min))*0x10000 + cur_lang;
    if (indented) {
        tail = new_null_box();
        link(head) = tail;
        width(tail) = par_indent;    
    }
    if (every_par != null) {
        begin_token_list(every_par, EVERY_PAR_TEXT);
    }
    if (nest_ptr == 1) {
        build_page(); // put |par_skip| glue on current page
    }
}
```
