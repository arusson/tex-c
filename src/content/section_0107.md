# Section 107

Then comes the multiplication of a scaled number by a fraction *n*$/$*d*, where *n* and *d* are nonnegative integers $\leq 2^{16}$ and *d* is positive.
It would be too dangerous to multiply by *n* and then divide by *d*, in separate operations, since overflow might well occur;
and it would be too inaccurate to divide by *d* and then multiply by *n*.
Hence this subroutine simulates 1.5-precision arithmetic.

```c arithmetic.c
scaled xn_over_d(scaled x, int n, int d) {
    bool positive = true; // was |x >= 0|?
    int t, u, v;          // intermediate quantities
    scaled quotient;
    if (x < 0) {
        negate(x);
        positive = false;
    }

    t = (x % 32768) * n;
    u = (x / 32768) * n + (t / 32768);
    v = (u % d) * 32768 + (t % 32768);
    if (u / d >= 32768) {
        arith_error = true;
    }
    else {
        u = 32768 * (u / d) + (v / d);
    }
    if (positive) {
        quotient = u;
        remainder_ = v % d;
    }
    else {
        quotient = -u;
        remainder_ = -(v % d);
    }
    return quotient;
}
```
