# Section 836

It is not necessary to create new active nodes having *minimal_demerits* greater than
*minimum_demerits + abs(adj_demerits)*, since such active nodes will never be chosen in the final paragraph breaks.
This observation allows us to omit a substantial number of feasible breakpoints from further consideration.

```c << Create new active nodes for the best feasible breaks just found >>=
if (no_break_yet) {
    // << Compute the values of |break_width| >>
}
// << Insert a delta node to prepare for breaks at |cur_p| >>
if (abs(adj_demerits) >= AWFUL_BAD - minimum_demerits) {
    minimum_demerits = AWFUL_BAD - 1;
}
else {
    minimum_demerits += abs(adj_demerits);
}
for(fit_class = VERY_LOOSE_FIT; fit_class <= TIGHT_FIT; fit_class++) {
    if (minimal_demerits[fit_class] <= minimum_demerits) {
        // << Insert a new active node from |best_place[fit_class]| to |cur_p| >>
    }
    minimal_demerits[fit_class] = AWFUL_BAD;
}
minimum_demerits = AWFUL_BAD;
// << Insert a delta node to prepare for the next active node >>
```
