# Section 1316

```c << Dump regions 5 and 6 of |eqtb| >>=
do {
    j = k;
    while (j < EQTB_SIZE) {
        if (eqtb[j].integer == eqtb[j + 1].integer) {
            goto found2;
        }
        incr(j);
    }
    l = EQTB_SIZE + 1;
    goto done2; // |j = EQTB_SIZE|
found2:
    incr(j);
    l = j;
    while (j < EQTB_SIZE) {
        if (eqtb[j].integer != eqtb[j + 1].integer) {
            goto done2;
        }
        incr(j);
    }
done2:
    dump_int(l - k);
    while (k < l) {
        dump_wd(eqtb[k]);
        incr(k);
    }
    k = j + 1;
    dump_int(k - l);
} while (k <= EQTB_SIZE);
```
