# Section 716

Here is a subroutine that creates a new glue specification from another one that is expressed in '`mu`', given the value of the math unit.

```c include/texmath.h
#define mu_mult(X) nx_plus_y(n, (X), xn_over_d((X), f, 0x10000))
```

```c math/math_subroutines.c
pointer math_glue(pointer g, scaled m) {
    pointer p; // the new glue specification
    int n;     // integer part of |m|
    scaled f;  // fraction part of |m|
    n = x_over_n(m, 0x10000);
    f = remainder_;
    if (f < 0) {
        decr(n);
        f = f + 0x10000;
    }
    p = get_node(GLUE_SPEC_SIZE);
    width(p) = mu_mult(width(g)); // convert mu to pt
    stretch_order(p) = stretch_order(g);
    if (stretch_order(p) == NORMAL) {
        stretch(p) = mu_mult(stretch(g));
    }
    else {
        stretch(p) = stretch(g);
    }
    shrink_order(p) = shrink_order(g);
    if (shrink_order(p) == NORMAL) {
        shrink(p) = mu_mult(shrink(g));
    }
    else {
        shrink(p) = shrink(g);
    }
    return p;
}
```
