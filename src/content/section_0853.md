# Section 853

Shrinkability is never infinite in a paragraph;
we can shrink the line from *r* to *cur_p* by at most *cur_active_width[6]*.

```c << Set the value of |b| to the badness for shrinking the line, and compute the corresponding |fit_class| >>=
if (-shortfall > cur_active_width[6]) {
    b = INF_BAD + 1;
}
else {
    b = badness(-shortfall, cur_active_width[6]);
}
if (b > 12) {
    fit_class = TIGHT_FIT;
}
else {
    fit_class = DECENT_FIT;
}
```
