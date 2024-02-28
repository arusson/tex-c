# Section 855

When we get to this part of the code, the line from *r* to *cur_p* is feasible, its badness is&nbsp;*b*, and its fitness classification is *fit_class*.
We don't want to make an active node for this break yet, but we will compute the total demerits and record them in the *minimal_demerits* array, if such a break is the current champion among all ways to get to *cur_p* in a given line-number class and fitness class.

```c << Record a new feasible break >>=
if (artificial_demerits) {
    d = 0;
}
else {
    // << Compute the demerits, |d|, from |r| to |cur_p| >>
}
#ifdef STAT
if (tracing_paragraphs > 0) {
    // << Print a symbolic description of this feasible break >>
}
#endif
d += total_demerits(r); // this is the minimum total demerits from the beginning to |cur_p| via |r|
if (d <= minimal_demerits[fit_class]) {
    minimal_demerits[fit_class] = d;
    best_place[fit_class] = break_node(r);
    best_pl_line[fit_class] = l;
    if (d < minimum_demerits) {
        minimum_demerits = d;
    }
}
```
