# Section 677

```c << Report an overfull vbox and |goto common_ending|, if this box is sufficiently bad >>=
if (-x - total_shrink[NORMAL] > vfuzz || vbadness < 100) {
    print_ln();
    print_nl("Overfull \\vbox (");
    print_scaled(-x - total_shrink[NORMAL]);
    print("pt too high");
    goto common_ending;
}
```
