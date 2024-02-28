# Section 889

Now *q* points to the hlist that represents the current line of the paragraph.
We need to compute the appropriate line width, pack the line into a box of this size, and shift the box by the appropriate amount of indentation.

```c << Call the packaging subroutine, setting |just_box| to the justified box >>=
if (cur_line > last_special_line) {
    cur_width = second_width;
    cur_indent = second_indent;
}
else if (par_shape_ptr == null) {
    cur_width = first_width;
    cur_indent = first_indent;
}
else {
    cur_width = mem[par_shape_ptr + 2*cur_line].sc;
    cur_indent = mem[par_shape_ptr + 2*cur_line - 1].sc;
}
adjust_tail = ADJUST_HEAD;
just_box = hpack(q, cur_width, EXACTLY);
shift_amount(just_box) = cur_indent;
```
