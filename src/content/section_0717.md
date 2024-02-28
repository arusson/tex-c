# Section 717

The *math_kern* subroutine removes *MU_GLUE* from a kern node, given the value of the math unit.

```c math/math_subroutines.c
void math_kern(pointer p, scaled m) {
    int n;    // integer part of |m|
    scaled f; // fraction part of |m|
    if (subtype(p) == MU_GLUE) {
        n = x_over_n(m, 0x10000);
        f = remainder_;
        if (f < 0) {
            decr(n);
            f += 0x10000;
        }
        width(p) = mu_mult(width(p));
        subtype(p) = EXPLICIT;
    }
}
```
