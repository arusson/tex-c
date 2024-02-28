# Section 974

```c include/constants.h
#define DEPLORABLE 100000 // more than |INF_BAD|, but less than |AWFUL_BAD|
```

```c << Check if node |p| is a new champion breakpoint; then |goto done| if |p| is a forced break or if the page-so-far is already too full >>=
if (pi < INF_PENALTY) {
    // << Compute the badness, |b|, using |AWFUL_BAD| if the box is too full >>
    if (b < AWFUL_BAD) {
        if (pi <= EJECT_PENALTY) {
            b = pi;
        }
        else if (b < INF_BAD) {
            b += pi;
        }
        else {
            b = DEPLORABLE;
        }
    }
    if (b <= least_cost) {
        best_place = p;
        least_cost = b;
        best_height_plus_depth = cur_height + prev_dp;
    }
    if (b == AWFUL_BAD || pi <= EJECT_PENALTY) {
        goto done;
    }
}
```
