# Section 810

```c << Make the unset node |r| into an |HLIST_NODE| of width |w|, setting the glue as if the width were |t| >>=
height(r) = height(q);
depth(r) = depth(q);
if (t == width(r)) {
    glue_sign(r) = NORMAL;
    glue_order(r) = NORMAL;
    set_glue_ratio_zero(glue_set(r));
}
else if (t > width(r)) {
    glue_sign(r) = STRETCHING;
    if (glue_stretch(r) == 0) {
        set_glue_ratio_zero(glue_set(r));
    }
    else {
        glue_set(r) = (double)(t - width(r)) / glue_stretch(r);
    }
}
else {
    glue_order(r) = glue_sign(r);
    glue_sign(r) = SHRINKING;
    if (glue_shrink(r) == 0) {
        set_glue_ratio_zero(glue_set(r));
    }
    else if (glue_order(r) == NORMAL && width(r) - t > glue_shrink(r)) {
        set_glue_ratio_one(glue_set(r));
    }
    else {
        glue_set(r) = (double)(width(r) - t) / glue_shrink(r);
    }    
}
width(r) = w;
type(r) = HLIST_NODE;
```
