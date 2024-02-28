# Section 869

The following code knows that discretionary texts contain only character nodes, kern nodes, box nodes, rule nodes, and ligature nodes.

```c << Try to break after a discretionary fragment, then |goto done5| >>=
s = pre_break(cur_p);
disc_width = 0;
if (s == null) {
    try_break(ex_hyphen_penalty, HYPHENATED);
}
else {
    do {
        // << Add the width of node |s| to |disc_width| >>
        s = link(s);
    } while (s != null);
    act_width += disc_width;
    try_break(hyphen_penalty, HYPHENATED);
    act_width -= disc_width;
}
r = replace_count(cur_p);
s = link(cur_p);
while (r > 0) {
    // << Add the width of node |s| to |act_width| >>
    decr(r);
    s = link(s);
}
prev_p = cur_p;
cur_p = s;
goto done5;
```
