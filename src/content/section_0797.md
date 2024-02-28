# Section 797

A span node is a 2-word record containing *width*, *info*, and *link* fields.
The *link* field is not really a link, it indicates the number of spanned columns; the *info* field points to a span node for the same starting column, having a greater extent of spanning, or to *END_SPAN*, which has the largest possible *link* field; the *width* field holds the largest natural width corresponding to a particular set of spanned columns.

A list of the maximum widths so far, for spanned columns starting at a given column, begins with the *info* field of the alignrecord for that column.

```c include/constants.h
#define SPAN_NODE_SIZE 2 // number of |mem| words for a span node
```

```c << Initialize the special list heads and constant nodes >>+=
link(END_SPAN) = MAX_QUARTERWORD + 1;
info(END_SPAN) = null;
```
