# Section 647

If the global variable *adjust_tail* is non-null, the *hpack* routine also removes all occurrences of *INS_NODE*, *MARK_NODE*, and *ADJUST_NODE* items and appends the resulting material onto the list that ends at location *adjust_tail*.

```c << Global variables >>+=
pointer adjust_tail; // tail of adjustment list
```
