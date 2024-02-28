# Section 1074

The global variable *cur_box* will point to a newly made box.
If the box is void, we will have *cur_box = null*.
Otherwise we will have *type(cur_box) = HLIST_NODE* or *VLIST_NODE* or *RULE_NODE*; the *RULE_NODE* case can occur only with leaders.

```c << Global variables >>+=
pointer cur_box; // box to be placed into its context
```
