# Section 678

```c << Report a tight vbox and |goto common_ending|, if this box is sufficiently bad >>=
last_badness = badness(-x, total_shrink[NORMAL]);
if (last_badness > vbadness) {
    print_ln();
    print_nl("Tight \\vbox (badness ");
    print_int(last_badness);
    goto common_ending;
}
```
