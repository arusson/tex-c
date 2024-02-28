# Section 1007

```c << Compute the badness, |b|, of the current page, using |AWFUL_BAD| if the box is too full >>=
if (page_total < page_goal) {
    if (page_so_far[3] != 0
        || page_so_far[4] != 0
        || page_so_far[5] != 0)
    {
        b = 0;
    }
    else {
        b = badness(page_goal - page_total, page_so_far[2]);
    }
}
else if (page_total - page_goal > page_shrink) {
    b = AWFUL_BAD;
}
else {
    b = badness(page_total - page_goal, page_shrink);
}
```
