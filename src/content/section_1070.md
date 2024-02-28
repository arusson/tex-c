# Section 1070

Here is where we clear the parameters that are supposed to revert to their default values after every paragraph and when internal vertical mode is entered.

```c builder/boxes_and_lists.c
void normal_paragraph() {
    if (looseness != 0) {
        eq_word_define(INT_BASE + LOOSENESS_CODE, 0);
    }
    if (hang_indent != 0) {
        eq_word_define(DIMEN_BASE + HANG_INDENT_CODE, 0);
    }
    if (hang_after != 1) {
        eq_word_define(INT_BASE + HANG_AFTER_CODE, 1);
    }
    if (par_shape_ptr != null) {
        eq_define(PAR_SHAPE_LOC, SHAPE_REF, null);
    }
}
```
