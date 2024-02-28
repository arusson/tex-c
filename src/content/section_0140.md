# Section 140

Insertions are represented by *INS_NODE* records, where the *subtype* indicates the corresponding box number.
For example, '`\insert 250`' leads to an *INS_NODE* whose *subtype* is *250 + MIN_QUARTERWORD*.
The *height* field of an *INS_NODE* is slightly misnamed; it actually holds the natural height plus depth of the vertical list being inserted.
The *depth* field holds the *split_max_depth* to be used in case this insertion is split, and the *split_top_ptr* points to the corresponding *split_top_skip*.
The *float_cost* field holds the *floating_penalty* that will be used if this insertion floats to a subsequent page after a split insertion of the same class.
There is one more field, the *ins_ptr*, which points to the beginning of the vlist for the insertion.

```c include/constants.h
#define INS_NODE      3 // |type| of insertion nodes
#define INS_NODE_SIZE 5 // number of words to allocate for an insertion
```

```c include/datastructures.h
#define float_cost(X)    mem[(X) + 1].integer // the |floating_penalty| to be used
#define ins_ptr(X)       info((X) + 4)        // the vertical list to be inserted
#define split_top_ptr(X) link((X) + 4)        // the |split_top_skip| to be used
```
