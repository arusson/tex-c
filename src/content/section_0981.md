# Section 981

The page builder has another data structure to keep track of insertions.
This is a list of four-word nodes, starting and ending at *PAGE_INS_HEAD*.
That is, the first element of the list is node $r_1$ = *link(PAGE_INS_HEAD)*;
node $r_j$ is followed by $r_{j + 1}$ = *link*($r_j$);
and if there are *n* items we have $r_{n + 1}$ = *PAGE_INS_HEAD*.
The *subtype* field of each node in this list refers to an insertion number; for example, '`\insert 250`' would correspond to a node whose *subtype* is 250 (the same as the *subtype* field of the relevant *INS_NODE*).
These *subtype* fields are in increasing order, and *subtype(PAGE_INS_HEAD)* = 255, so *PAGE_INS_HEAD* serves as a convenient sentinel at the end of the list.
A record is present for each insertion number that appears in the current page.

The *type* field in these nodes distinguishes two possibilities that might occur as we look ahead before deciding on the optimum page break.
If *type(r) = INSERTING*, then *height(r)* contains the total of the height-plus-depth dimensions of the box and all its inserts seen so far.
If *type(r) = SPLIT_UP*, then no more insertions will be made into this box, because at least one previous insertion was too big to fit on the current page; *broken_ptr(r)* points to the node where that insertion will be split, if $\TeX$ decides to split it, *broken_ins(r)* points to the insertion node that was tentatively split, and *height(r)* includes also the natural height plus depth of the part that would be split off.

In both cases, *last_ins_ptr(r)* points to the last *INS_NODE* encountered for box *subtype(r)* that would be at least partially inserted on the next page; and *best_ins_ptr(r)* points to the last such *INS_NODE* that should actually be inserted, to get the page with minimum badness among all page breaks considered so far.
We have *best_ins_ptr(r) = null* if and only if no insertion for this box should be made to produce this optimum page.

The data structure definitions here use the fact that the *height* field appears in the fourth word of a box node.

```c include/constants.h
#define PAGE_INS_NODE_SIZE 4 // number of words for a page insertion node
#define INSERTING          0 // an insertion class that has not yet overflowed
#define SPLIT_UP           1 // an overflowed insertion class
```

```c include/builder.h
#define broken_ptr(X)   link((X) + 1) // an insertion for this class will break here if anywhere
#define broken_ins(X)   info((X) + 1) // this insertion might break at |broken_ptr|
#define last_ins_ptr(X) link((X) + 2) // the most recent insertion for this |subtype|
#define best_ins_ptr(X) info((X) + 2) // the optimum most recent insertion
```

```c << Initialize the special list heads and constant nodes >>+=
subtype(PAGE_INS_HEAD) = 255;
type(PAGE_INS_HEAD) = SPLIT_UP;
link(PAGE_INS_HEAD) = PAGE_INS_HEAD;
```
