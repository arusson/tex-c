# Section 181

A global variable called *depth_threshold* is used to record the maximum depth of nesting for which *show_node_list* will show information.
If we have *depth_threshold = 0*, for example, only the top level information will be given and no sublists will be traversed.
Another global variable, called *breadth_max*, tells the maximum number of items to show at each level;
*breadth_max* had better be positive, or you won't see anything.

```c << Global variables >>+=
int depth_threshold; // maximum nesting depth in box displays
int breadth_max;    // maximum number of items shown at the same list level
```
