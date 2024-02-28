# Section 660

```c << Report an underfull hbox and |goto common_ending|, if this box is sufficiently bad >>=
last_badness = badness(x, total_stretch[NORMAL]);
if (last_badness > hbadness) {
    print_ln();
    if (last_badness > 100) {
        print_nl("Underfull");
    }
    else {
        print_nl("Loose");
    }
    print(" \\hbox (badness ");
    print_int(last_badness);
    goto common_ending;
}
```
