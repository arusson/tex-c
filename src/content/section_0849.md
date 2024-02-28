# Section 849

```c << Set line length parameters in preparation for hanging indentation >>=
last_special_line = abs(hang_after);
if (hang_after < 0) {
    first_width = hsize - abs(hang_indent);
    if (hang_indent >= 0) {
        first_indent = hang_indent;
    }
    else {
        first_indent = 0;
    }
    second_width = hsize;
    second_indent = 0;
}
else {
    first_width = hsize;
    first_indent = 0;
    second_width = hsize - abs(hang_indent);
    if (hang_indent >= 0) {
        second_indent = hang_indent;
    }
    else {
        second_indent = 0;
    }
}
```
