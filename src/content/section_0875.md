# Section 875

The adjustment for a desired looseness is a slightly more complicated version of the loop just considered.
Note that if a paragraph is broken into segments by displayed equations, each segment will be subject to the looseness calculation, independently of the other segments.

```c << Find the best active node for the desired looseness >>=
r = link(ACTIVE);
actual_looseness = 0;
do {
    if (type(r) != DELTA_NODE) {
        line_diff = line_number(r) - best_line;
        if ((line_diff < actual_looseness && looseness <= line_diff)
            || (line_diff > actual_looseness && looseness >= line_diff))
        {
            best_bet = r;
            actual_looseness = line_diff;
            fewest_demerits = total_demerits(r);
        }
        else if (line_diff == actual_looseness && total_demerits(r) < fewest_demerits) {
            best_bet = r;
            fewest_demerits = total_demerits(r);
        }
    }
    r = link(r);
} while (r != LAST_ACTIVE);
best_line = line_number(best_bet);
```
