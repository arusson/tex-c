# Section 705

The *overbar* function returns a pointer to a vlist box that consists of a given box *b*, above which has been placed a kern of height *k* under a fraction rule of thickness *t* under additional space of height *t*.

```c math/math_subroutines.c
pointer overbar(pointer b, scaled k, scaled t) {
    pointer p, q; // nodes being constructed
    p = new_kern(k);
    link(p) = b;
    q = fraction_rule(t);
    link(q) = p;
    p = new_kern(t);
    link(p) = q;
    return vpack(p, NATURAL);
}
```
