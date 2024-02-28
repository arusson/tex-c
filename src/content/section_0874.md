# Section 874

```c << Find an active node with fewest demerits >>=
r = link(ACTIVE);
fewest_demerits = AWFUL_BAD;
do {
    if (type(r) != DELTA_NODE && total_demerits(r) < fewest_demerits) {
        fewest_demerits = total_demerits(r);
        best_bet = r;
    }
    r = link(r);
} while (r != LAST_ACTIVE);
best_line = line_number(best_bet);
```
