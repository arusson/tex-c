# Section 1317

```c << Undump regions 1 to 6 of |eqtb| >>=
k = ACTIVE_BASE;
do {
    undump_int(x);
    if (x < 1 || k + x > EQTB_SIZE + 1) {
        goto bad_fmt;
    }
    for(j = k; j <= k + x - 1; j++) {
        undump_wd(eqtb[j]);
    }
    k += x;
undump_int(x);
if (x < 0 || k + x > EQTB_SIZE + 1) {
    goto bad_fmt;
}
for(j = k; j <= k + x - 1; j++) {
    eqtb[j] = eqtb[k - 1];
}
k += x;
} while (k <= EQTB_SIZE);
```
