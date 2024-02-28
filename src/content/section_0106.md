# Section 106

We also need to divide scaled dimensions by integers.

```c arithmetic.c
scaled x_over_n(scaled x, int n) {
    bool negative = false;  // should |remainder_| be negated?
    scaled quotient;
    if (n == 0) {
        arith_error = true;
        quotient = 0;
        remainder_ = x;
    }
    else {
        if (n < 0) {
            negate(x);
            negate(n);
            negative = true;
        }
        if (x >= 0) {
            quotient = x / n;
            remainder_ = x % n;
        }
        else {
            quotient = -((-x) / n);
            remainder_ = -((-x) % n);
        }
    }
    if (negative) {
        negate(remainder_);
    }
    return quotient;
}
```
