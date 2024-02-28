# Section 147

A *MATH_NODE*, which occurs only in horizontal lists, appears before and after mathematical formulas.
The *subtype* field is *before* before the formula and *after* after it.
There is a *width* field, which represents the amount of surrounding space inserted by `\mathsurround`.

```c include/constants.h
#define MATH_NODE 9 // |type| of a math node
#define BEFORE    0 // |subtype| for math node that introduces a formula
#define AFTER     1 // |subtype| for math node that winds up a formula
```

```c datastructures/nodes.c
pointer new_math(scaled w, small_number s) {
    pointer p = get_node(SMALL_NODE_SIZE); // the new node
    type(p) = MATH_NODE;
    subtype(p) = s;
    width(p) = w;
    return p;
}
```
