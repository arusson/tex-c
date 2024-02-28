# Section 1038

The result of `\char` can participate in a ligature or kern, so we must look ahead for it.

```c << Look ahead for another character, or leave |lig_stack| empty if there's none there >>=
get_next(); // set only |cur_cmd| and |cur_chr|, for speed
if (cur_cmd == LETTER
    || cur_cmd == OTHER_CHAR
    || cur_cmd == CHAR_GIVEN)
{
    goto main_loop_lookahead_1;
}
x_token(); // now expand and set |cur_cmd|, |cur_chr|, |cur_tok|
if (cur_cmd == LETTER
    || cur_cmd == OTHER_CHAR
    || cur_cmd == CHAR_GIVEN)
{
    goto main_loop_lookahead_1;
}
if (cur_cmd == CHAR_NUM) {
    scan_char_num();
    cur_chr = cur_val;
    goto main_loop_lookahead_1;
}
if (cur_cmd == NO_BOUNDARY) {
    bchar = NON_CHAR;
}
cur_r = bchar;
lig_stack = null;
goto main_lig_loop;

main_loop_lookahead_1:
adjust_space_factor;
fast_get_avail(lig_stack);
font(lig_stack) = main_f;
cur_r = cur_chr;
character(lig_stack) = cur_r;
if (cur_r == false_bchar) {
    cur_r = NON_CHAR; // this prevents spurious ligatures
}
```
