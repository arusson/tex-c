# Section 751

We use *shift_up* and *shift_down* in the following program for the amount of glue between the displayed operator *y* and its limits *x* and *z*.
The vlist inside box *v* will consist of *x* followed by *y* followed by *z*, with kern nodes for the spaces between and around them.

```c << Attach the limits to |y| and adjust |height(v)|, |depth(v)| to account for their presence >>=
if (math_type(supscr(q)) == EMPTY) {
    free_node(x, BOX_NODE_SIZE);
    list_ptr(v) = y;
}
else {
    shift_up = big_op_spacing3 - depth(x);
    if (shift_up < big_op_spacing1) {
        shift_up = big_op_spacing1;
    }
    p = new_kern(shift_up);
    link(p) = y;
    link(x) = p;
    p = new_kern(big_op_spacing5);
    link(p) = x;
    list_ptr(v) = p;
    height(v) += big_op_spacing5 + height(x) + depth(x) + shift_up;
}
if (math_type(subscr(q)) == EMPTY) {
    free_node(z, BOX_NODE_SIZE);
}
else {
    shift_down = big_op_spacing4 - height(z);
    if (shift_down < big_op_spacing2) {
        shift_down = big_op_spacing2;
    }
    p = new_kern(shift_down);
    link(y) = p;
    link(p) = z;
    p = new_kern(big_op_spacing5);
    link(z) = p;
    depth(v) += big_op_spacing5 + height(z) + depth(z) + shift_down;
}
```
