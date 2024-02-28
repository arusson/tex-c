# Section 704

Here is a function that returns a pointer to a rule node having a given thickness *t*.
The rule will extend horizontally to the boundary of the vlist that eventually contains it.

```c math/math_subroutines.c
// << Start file |math_subroutines.c| >>

// construct the bar for a fraction
pointer fraction_rule(scaled t) {
    pointer p; // the new node
    p = new_rule();
    height(p) = t;
    depth(p) = 0;
    return p;
}
```
