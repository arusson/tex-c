# Section 1315

The table of equivalents usually contains repeated information, so we dump it in compressed form: The sequence of *n + 2* values (*n*, $x_1$, $\ldots$, $x_n$, *m*) in the format file represents *n + m* consecutive entries of *eqtb*, with *m* extra copies of $x_n$, namely ($x_1$, $\ldots$, $x_n$, $x_n$, $\ldots$, $x_n$).

```c << Dump regions 1 to 4 of |eqtb| >>=
k = ACTIVE_BASE;
do {
    j = k;
    while (j < INT_BASE - 1) {
        if (equiv(j) == equiv(j + 1)
            && eq_type(j) == eq_type(j + 1)
            && eq_level(j) == eq_level(j + 1))
        {
            goto found1;
        }
        incr(j);
    }
    l = INT_BASE;
    goto done1; // |j = INT_BASE - 1|
found1:
    incr(j);
    l = j;
    while (j < INT_BASE - 1) {
        if (equiv(j) != equiv(j + 1)
            || eq_type(j) != eq_type(j + 1)
            || eq_level(j) != eq_level(j + 1))
        {
            goto done1;
        }
        incr(j);
    }
done1:
    dump_int(l - k);
    while (k < l) {
        dump_wd(eqtb[k]);
        incr(k);
    }
    k = j + 1;
    dump_int(k - l);
} while (k != INT_BASE);
```
