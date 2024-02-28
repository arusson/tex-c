# Section 970

The next subroutine finds the best place to break a given vertical list so as to obtain a box of height&nbsp;*h*, with maximum depth&nbsp;*d*.
A pointer to the beginning of the vertical list is given, and a pointer to the optimum breakpoint is returned.
The list is effectively followed by a forced break, i.e., a penalty node with the *EJECT_PENALTY*;
if the best break occurs at this artificial node, the value *null* is returned.

An array of six *scaled* distances is used to keep track of the height from the beginning of the list to the current place, just as in *line_break*.
In fact, we use one of the same arrays, only changing its name to reflect its new significance.

```c include/breaker.h
#define active_height      active_width           // new name for the six distance variables
#define cur_height         active_height[1]       // the natural height
#define set_height_zero(X) active_height[(X)] = 0 // initialize the height to zero
```

```c breaker/page_break.c
// finds optimum page break
pointer vert_break(pointer p, scaled h, scaled d) {
    pointer prev_p;            // if |p| is a glue node, |type(prev_p)| determines whether |p| is a legal breakpoint
    pointer q, r;              // glue specifications
    int pi = 0;                // penalty value
    int b;                     // badness at a trial breakpoint
    int least_cost;            // the smallest badness plus penalties found so far
    pointer best_place = null; // the most recent break that leads to |least_cost|
    scaled prev_dp;            // depth of previous box in the list
    small_number t;            // |type| of the node following a kern
    
    prev_p = p; // an initial glue node is not a legal breakpoint
    least_cost = AWFUL_BAD;
    do_all_six(set_height_zero);
    prev_dp = 0;
    while(true) {
        // << If node |p| is a legal breakpoint, check if this break is the best known, and |goto done| if |p| is null or if the page-so-far is already too full to accept more stuff >>
        prev_p = p;
        p = link(prev_p);
    }
done:
    return best_place;
}
```
