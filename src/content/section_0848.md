# Section 848

We compute the values of *easy_line* and the other local variables relating to line length when the *line_break* procedure is initializing itself.

```c << Get ready to start line breaking >>+=
if (par_shape_ptr == null) {
    if (hang_indent == 0) {
        last_special_line = 0;
        second_width = hsize;
        second_indent = 0;
    }
    else {
        // << Set line length parameters in preparation for hanging indentation >>
    }
}
else {
    last_special_line = info(par_shape_ptr) - 1;
    second_width = mem[par_shape_ptr + 2*(last_special_line + 1)].sc;
    second_indent = mem[par_shape_ptr + 2*last_special_line + 1].sc;
}
if (looseness == 0) {
    easy_line = last_special_line;
}
else {
    easy_line = MAX_HALFWORD;
}
```
