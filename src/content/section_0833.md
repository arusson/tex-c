# Section 833

As we consider various ways to end a line at *cur_p*, in a given line number class, we keep track of the best total demerits known, in an array with one entry for each of the fitness classifications.
For example, *minimal_demerits[TIGHT_FIT]* contains the fewest total demerits of feasible line breaks ending at *cur_p* with a *TIGHT_FIT* line; *best_place[TIGHT_FIT]* points to the passive node for the break before&nbsp;*cur_p* that achieves such an optimum; and *best_pl_line[TIGHT_FIT]* is the *line_number* field in the active node corresponding to *best_place[TIGHT_FIT]*.
When no feasible break sequence is known, the *minimal_demerits* entries will be equal to *AWFUL_BAD*, which is $2^{30} - 1$.
Another variable, *minimum_demerits*, keeps track of the smallest value in the *minimal_demerits* array.

```c include/constants.h
#define AWFUL_BAD 0x3fffffff // more than a billion demerits
```

```c << Global variables >>+=
int minimal_demerits[4];  // best total demerits known for current line class and position, given the fitness
int minimum_demerits;     // best total demerits known for current line class and position
pointer best_place[4];    // how to achieve |minimal_demerits|
halfword best_pl_line[4]; // corresponding line number
```
