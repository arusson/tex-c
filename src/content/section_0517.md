# Section 517

The third.

```c parser/filenames.c
void end_name() {
    if (str_ptr + 3 > MAX_STRINGS) {
        overflow("number of strings", MAX_STRINGS - init_str_ptr);
    }
    if (area_delimiter == 0) {
        cur_area = EMPTY_STRING;
    }
    else {
        cur_area = str_ptr;
        str_start[str_ptr + 1] = str_start[str_ptr] + area_delimiter;
        incr(str_ptr);
    }
    if (ext_delimiter == 0) {
        cur_ext = EMPTY_STRING;
        cur_name = make_string();
    }
    else {
        cur_name = str_ptr;
        str_start[str_ptr + 1] = str_start[str_ptr] + ext_delimiter - area_delimiter - 1;
        incr(str_ptr);
        cur_ext = make_string();
    }
}
```
