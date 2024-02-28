# Section 1061

```c builder/boxes_and_lists.c
void append_kern() {
    quarterword s; // |subtype| of the kern node
    s = cur_chr;
    scan_dimen(s == MU_GLUE, false, false);
    tail_append(new_kern(cur_val));
    subtype(tail) = s;
}
```
