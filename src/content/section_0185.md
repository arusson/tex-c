# Section 185

```c << Display special fields of the unset node |p| >>=
if (span_count(p) != MIN_QUARTERWORD) {
    print(" (");
    print_int(span_count(p) + 1);
    print(" columns)");
}
if (glue_stretch(p) != 0) {
    print(", stretch ");
    print_glue(glue_stretch(p), glue_order(p), "");
}
if (glue_shrink(p) != 0) {
    print(", shrink ");
    print_glue(glue_shrink(p), glue_sign(p), "");
}
```
