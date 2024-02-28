# Section 852

When a line must stretch, the available stretchability can be found in the subarray *cur_active_width[2 .. 5]*, in units of points, fil, fill, and filll.

The present section is part of $\TeX$'s inner loop, and it is most often performed when the badness is infinite;
therefore it is worth while to make a quick test for large width excess and small stretchability, before calling the *badness* subroutine.

```c << Set the value of |b| to the badness for stretching the line, and compute the corresponding |fit_class| >>=
if (cur_active_width[3] != 0
    || cur_active_width[4] != 0
    || cur_active_width[5] != 0)
{
    b = 0;
    fit_class = DECENT_FIT; // infinite stretch
}
else if (shortfall > 7230584 && cur_active_width[2] < 1663497) {
    b = INF_BAD;
    fit_class = VERY_LOOSE_FIT;
}
else {
    b = badness(shortfall, cur_active_width[2]);
    if (b > 12) {
        if (b > 99) {
            fit_class = VERY_LOOSE_FIT;
        }
        else {
            fit_class = LOOSE_FIT;
        }
    }
    else {
        fit_class = DECENT_FIT;
    }
}
```
