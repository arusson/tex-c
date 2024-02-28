# Section 1124

```c << Create a character node |q| for the next character, but set |q = null| if problems arise >>=
q = null;
f = cur_font;
if (cur_cmd == LETTER
    || cur_cmd == OTHER_CHAR
    || cur_cmd == CHAR_GIVEN)
{
    q = new_character(f, cur_chr);
}
else if (cur_cmd == CHAR_NUM) {
    scan_char_num();
    q = new_character(f, cur_val);
}
else {
    back_input();
}
```
