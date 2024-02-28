# Section 1200

```c math/math_lists.c
void resume_after_display() {
    if (cur_group != MATH_SHIFT_GROUP) {
        confusion("display");
    }
    unsave();
    prev_graf += 3;
    push_nest();
    mode = HMODE;
    space_factor = 1000;
    set_cur_lang;
    clang = cur_lang;
    prev_graf = (norm_min(left_hyphen_min)*64 + norm_min(right_hyphen_min))*0x10000 + cur_lang;
    // << Scan an optional space >>
    if (nest_ptr == 1) {
        build_page();
    }
}
```
