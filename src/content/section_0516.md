# Section 516

And here's the second.
The string pool might change as the file name is being scanned, since a new `\csname` might be entered; therefore we keep *area_delimiter* and *ext_delimiter* relative to the beginning of the current string, instead of assigning an absolute address like *pool_ptr* to them.

```c parser/filenames.c
bool more_name(ASCII_code c) {
    if (c == ' ') {
        return false;
    }
    else {
        str_room(1);
        append_char(c); // contribute |c| to the current string
        if (c == '/') {
            area_delimiter = cur_length;
            ext_delimiter = 0;
        }
        else if (c == '.' && ext_delimiter == 0) {
            ext_delimiter = cur_length;
        }
        return true;
    }
}
```
