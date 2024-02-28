# Section 888

```c << Append the new box to the current vertical list, followed by the list of special nodes taken out of the box by the packager >>=
append_to_vlist(just_box);
if (ADJUST_HEAD != adjust_tail) {
    link(tail) = link(ADJUST_HEAD);
    tail = adjust_tail;
}
adjust_tail = null;
```
