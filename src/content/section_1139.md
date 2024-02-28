# Section 1139

```c << Go into ordinary math mode >>=
push_math(MATH_SHIFT_GROUP);
eq_word_define(INT_BASE + CUR_FAM_CODE, -1);
if (every_math != null) {
    begin_token_list(every_math, EVERY_MATH_TEXT);
}
```
