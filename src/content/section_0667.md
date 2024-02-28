# Section 667

```c << Report a tight hbox and |goto common_ending|, if this box is sufficiently bad >>=
last_badness = badness(-x, total_shrink[NORMAL]);
if (last_badness > hbadness) {
    print_ln();
    print_nl("Tight \\hbox (badness ");
    print_int(last_badness);
    goto common_ending;
}
```
