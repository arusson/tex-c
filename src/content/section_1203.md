# Section 1203

If the equation number is set on a line by itself, either before or after the formula, we append an infinite penalty so that no page break will separate the display from its number; and we use the same size and displacement for all three potential lines of the display, even though '`\parshape`' may specify them differently.

```c << Append the glue or equation number preceding the display >>=
tail_append(new_penalty(pre_display_penalty));
if (d + s <= pre_display_size || l) {
     // not enough clearance
    g1 = ABOVE_DISPLAY_SKIP_CODE;
    g2 = BELOW_DISPLAY_SKIP_CODE;
}
else {
    g1 = ABOVE_DISPLAY_SHORT_SKIP_CODE;
    g2 = BELOW_DISPLAY_SHORT_SKIP_CODE;
}
if (l && e == 0) {
    // it follows that |type(a) = HLIST_NODE|
    shift_amount(a) = s;
    append_to_vlist(a);
    tail_append(new_penalty(INF_PENALTY));
}
else {
    tail_append(new_param_glue(g1));
}
```
