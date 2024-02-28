# Section 1199

At this time *p* points to the mlist for the formula; *a* is either *null* or it points to a box containing the equation number; and we are in vertical mode (or internal vertical mode).

```c << Finish displayed math >>=
cur_mlist = p;
cur_style = DISPLAY_STYLE;
mlist_penalties = false;
mlist_to_hlist();
p = link(TEMP_HEAD);
adjust_tail = ADJUST_HEAD;
b = hpack(p, NATURAL);
p = list_ptr(b);
t = adjust_tail;
adjust_tail = null;
w = width(b);
z = display_width;
s = display_indent;
if (a == null || danger) {
    e = 0;
    q = 0;
}
else {
    e = width(a);
    q = e + math_quad(TEXT_SIZE);
}
if (w + q > z) {
    // << Squeeze the equation as much as possible; if there is an equation number that should go on a separate line by itself, set |e = 0| >>
}

// << Determine the displacement, |d|, of the left edge of the equation, with respect to the line size |z|, assuming that |l = false| >>

// << Append the glue or equation number preceding the display >>
// << Append the display and perhaps also the equation number >>
// << Append the glue or equation number following the display >>
resume_after_display();
```
