# Section 971

A global variable *best_height_plus_depth* will be set to the natural size of the box that corresponds to the optimum breakpoint found by *vert_break*.
(This value is used by the insertion-splitting algorithm of the page builder.)

```c << Global variables >>+=
scaled best_height_plus_depth; // height of the best box, without stretching or shrinking
```
