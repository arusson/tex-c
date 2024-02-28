# Section 804

Now the preamble list has been converted to a list of alternating unset boxes and tabskip glue, where the box widths are equal to the final column sizes.
In case of `\valign`, we change the widths to heights, so that a correct error message will be produced if the alignment is overfull or underfull.

```c << Package the preamble list, to determine the actual tabskip glue amounts, and let |p| point to this prototype box >>=
save_ptr -= 2;
pack_begin_line = -mode_line;
if (mode == -VMODE) {
    rule_save = overfull_rule;
    overfull_rule = 0; // prevent rule from being packaged
    p = hpack(preamble, saved(1), saved(0));
    overfull_rule = rule_save;
}
else {
    q = link(preamble);
    do {
        height(q) = width(q);
        width(q) = 0;
        q = link(link(q));
    } while (q != null);
    p = vpack(preamble, saved(1), saved(0));
    q = link(preamble);
    do {
        width(q) = height(q);
        height(q) = 0;
        q = link(link(q));
    } while (q != null);
}
pack_begin_line = 0;
```
