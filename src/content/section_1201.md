# Section 1201

The user can force the equation number to go on a separate line by causing its width to be zero.

```c << Squeeze the equation as much as possible; if there is an equation number that should go on a separate line by itself, set |e = 0| >>=
if (e != 0 && (w - total_shrink[NORMAL] + q <= z
    || total_shrink[FIL] != 0
    || total_shrink[FILL] != 0
    || total_shrink[FILLL] != 0))
{
    free_node(b, BOX_NODE_SIZE);
    b = hpack(p, z - q, EXACTLY);
}
else {
    e = 0;
    if (w > z) {
        free_node(b, BOX_NODE_SIZE);
        b = hpack(p, z, EXACTLY);
    }
}
w = width(b);
```
