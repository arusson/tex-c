# Section 850

When we come to the following code, we have just encountered the first active node&nbsp;*r* whose *line_number* field contains $l$.
Thus we want to compute the length of the $l$-th line of the current paragraph.
Furthermore, we want to set *old_l* to the last number in the class of line numbers equivalent to&nbsp;$l$.

```c << Compute the new line width >>=
if (l > easy_line) {
    line_width = second_width;
    old_l = MAX_HALFWORD - 1;
}
else {
    old_l = l;
    if (l > last_special_line) {
        line_width = second_width;
    }
    else if (par_shape_ptr == null) {
        line_width = first_width;
    }
    else {
        line_width = mem[par_shape_ptr + 2*l].sc;
    }
}
```
