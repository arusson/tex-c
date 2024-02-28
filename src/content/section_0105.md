# Section 105

The first arithmetical subroutine we need computes *nx + y*, where *x* and *y* are *scaled* and *n* is an integer.
We will also use it to multiply integers.

```c include/arithmetic.h
// << Start file |arithmetic.h| >>

#define nx_plus_y(A, B, C)  mult_and_add((A), (B), (C), 0x3fffffff)
#define mult_integers(A, B) mult_and_add((A), (B), 0, 0x7fffffff)
```

```c arithmetic.c
scaled mult_and_add(int n, scaled x, scaled y, scaled max_answer) {
    scaled res;
    if (n < 0) {
        negate(x);
        negate(n);
    }
    if (n == 0) {
        res = y;
    }
    else if ((x <= (max_answer - y) / n)
        && (-x <= (max_answer + y) / n))
    {
        res  = n * x + y;
    }
    else {
        arith_error = true;
        res = 0;
    }
    return res;
}
```
