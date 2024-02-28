# Section 674

```c << Report an underfull vbox and |goto common_ending|, if this box is sufficiently bad >>=
last_badness = badness(x, total_stretch[NORMAL]);
if (last_badness > vbadness) {
    print_ln();
    if (last_badness > 100) {
        print_nl("Underfull");
    }
    else {
        print_nl("Loose");
    }
    print(" \\vbox (badness ");
    print_int(last_badness);
    goto common_ending;
}
```
