# Section 1249

Here's something that isn't quite so obvious.
It guarantees that *info(par_shape_ptr)* can hold any positive&nbsp;*n* for which *get_node(2\*n + 1)* doesn't overflow the memory capacity.

```c << Check the "constant" values for consistency >>+=
if (2*MAX_HALFWORD < MEM_TOP - MEM_MIN) {
    bad = 41;
}
```
