# Section 102

The following function is used to create a scaled integer from a given decimal fraction $(.d_0d_1\ldots d_{k - 1})$, where *0* $\leq$ *k* $\leq$ *17*.
The digit $d_i$ is given in *dig[i]*, and the calculation produces a correctly rounded result.

```c arithmetic.c
// converts a decimal fraction
scaled round_decimals(small_number k) {
    int a = 0; // the accumulator
    while (k > 0) {
        decr(k);
        a = (a + dig[k] * TWO) / 10;
    }
    return (a + 1) / 2;
}
```
