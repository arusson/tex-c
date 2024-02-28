# Section 1004

```c << Update the current page measurements with respect to the glue or kern specified by node |p| >>=
if (type(p) == KERN_NODE) {
    q = p;
}
else {
    q = glue_ptr(p);
    page_so_far[2 + stretch_order(q)] += stretch(q);
    page_shrink += shrink(q);
    if (shrink_order(q) != NORMAL && shrink(q) != 0) {
        print_err("Infinite glue shrinkage found on current page");
        help4("The page about to be output contains some infinitely")
            ("shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.")
            ("Such glue doesn't belong there; but you can safely proceed,")
            ("since the offensive shrinkability has been made finite.");
        error();
        r = new_spec(q);
        shrink_order(r) = NORMAL;
        delete_glue_ref(q);
        glue_ptr(p) = r;
        q = r;
    }
}
page_total += page_depth + width(q);
page_depth = 0;
```
