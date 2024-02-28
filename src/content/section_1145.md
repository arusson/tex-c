# Section 1145

When we enter display math mode, we need to call *line_break* to process the partial paragraph that has just been interrupted by the display.
Then we can set the proper values of *display_width* and *display_indent* and *pre_display_size*.

```c << Go into display math mode >>=
if (head == tail) {
    // '\noindent$$' or '$$ $$'
    pop_nest();
    w = -MAX_DIMEN;
}
else {
    line_break(display_widow_penalty);
    // << Calculate the natural width, |w|, by which the characters of the final line extend to the right of the reference point, plus two ems; or set |w = MAX_DIMEN| if the non-blank information on that line is affected by stretching or shrinking >>
}
// now we are in vertical mode, working on the list that will contain the display

// << Calculate the length, |l|, and the shift amount, |s|, of the display lines >>
push_math(MATH_SHIFT_GROUP);
mode = MMODE;
eq_word_define(INT_BASE + CUR_FAM_CODE, -1);
eq_word_define(DIMEN_BASE + PRE_DISPLAY_SIZE_CODE, w);
eq_word_define(DIMEN_BASE + DISPLAY_WIDTH_CODE, l);
eq_word_define(DIMEN_BASE + DISPLAY_INDENT_CODE, s);
if (every_display != null) {
    begin_token_list(every_display, EVERY_DISPLAY_TEXT);
}
if (nest_ptr == 1) {
    build_page();
}
```
