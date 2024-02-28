# Section 811

```c << Make the unset node |r| into a |VLIST_NODE| of height |w|, setting the glue as if the height were |t| >>=
width(r) = width(q);
if (t == height(r)) {
    glue_sign(r) = NORMAL;
    glue_order(r) = NORMAL;
    set_glue_ratio_zero(glue_set(r));
}
else if (t > height(r)) {
    glue_sign(r) = STRETCHING;
    if (glue_stretch(r) == 0) {
        set_glue_ratio_zero(glue_set(r));
    }
    else {
        glue_set(r) = (double)(t - height(r)) / glue_stretch(r);
    }
}
else {
    glue_order(r) = glue_sign(r);
    glue_sign(r) = SHRINKING;
    if (glue_shrink(r) == 0) {
        set_glue_ratio_zero(glue_set(r));
    }
    else if (glue_order(r) == NORMAL && height(r) - t > glue_shrink(r)) {
        set_glue_ratio_one(glue_set(r));
    }
    else {
        glue_set(r) = (double)(height(r) - t) / glue_shrink(r);
    }
}
height(r) = w;
type(r) = VLIST_NODE;
```
