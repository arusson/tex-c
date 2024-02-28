# Section 976

Vertical lists that are subject to the *vert_break* procedure should not contain infinite shrinkability, since that would permit any amount of information to "fit" on one page.

```c << Update the current height and depth measurements with respect to a glue or kern node |p| >>=
if (type(p) == KERN_NODE) {
    q = p;
}
else {
    q = glue_ptr(p);
    active_height[2 + stretch_order(q)] += stretch(q);
    active_height[6] += shrink(q);
    if (shrink_order(q) != NORMAL && shrink(q) != 0) {
        print_err("Infinite glue shrinkage found in box being split");
        help4("The box you are \\vsplitting contains some infinitely")
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
cur_height += prev_dp + width(q);
prev_dp = 0;
```
