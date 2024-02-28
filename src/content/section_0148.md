# Section 148

$\TeX$ makes use of the fact that *HLIST_NODE*, *VLIST_NODE*, *RULE_NODE*, *INS_NODE*, *MARK_NODE*, *ADJUST_NODE*, *LIGATURE_NODE*, *DISC_NODE*, *WHATSIT_NODE*, and *MATH_NODE* are at the low end of the type codes, by permitting a break at glue in a list if and only if the *type* of the previous node is less than *MATH_NODE*.
Furthermore, a node is discarded after a break if its type is *MATH_NODE* or more.

```c include/datastructures.h
#define precedes_break(X)  (type((X)) < MATH_NODE)
#define non_discardable(X) (type((X)) < MATH_NODE)
```
