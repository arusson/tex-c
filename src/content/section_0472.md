# Section 472

```c << Print the result of command |c| >>=
switch (c) {
case NUMBER_CODE:
    print_int(cur_val);
    break;

case ROMAN_NUMERAL_CODE:
    print_roman_int(cur_val);
    break;

case STRING_CODE:
    if (cur_cs != 0) {
        sprint_cs(cur_cs);
    }
    else {
        print_char(cur_chr);
    }
    break;

case MEANING_CODE:
    print_meaning();
    break;

case FONT_NAME_CODE:
    print_strnumber(font_name[cur_val]);
    if (font_size[cur_val] != font_dsize[cur_val]) {
        print(" at ");
        print_scaled(font_size[cur_val]);
        print("pt");
    }
    break;

case JOB_NAME_CODE:
    print_strnumber(job_name);
} // there are no other cases
```
