# Section 666

```c << Report an overfull hbox and |goto common_ending|, if this box is sufficiently bad >>=
if (-x - total_shrink[NORMAL] > hfuzz || hbadness < 100) {
    if (overfull_rule > 0 && -x - total_shrink[NORMAL] > hfuzz) {
        while (link(q) != null) {
            q = link(q);
        }
        link(q) = new_rule();
        width(link(q)) = overfull_rule;
    }
    print_ln();
    print_nl("Overfull \\hbox (");
    print_scaled(-x - total_shrink[NORMAL]);
    print("pt too wide");
    goto common_ending;
}
```
