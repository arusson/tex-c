# Section 1077

```c << Store |cur_box| in a box register >>=
if (box_context < BOX_FLAG + 256) {
    eq_define(BOX_BASE - BOX_FLAG + box_context, BOX_REF, cur_box);
}
else {
    geq_define(BOX_BASE - BOX_FLAG - 256 + box_context, BOX_REF, cur_box);
}
```
