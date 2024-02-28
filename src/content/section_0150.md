# Section 150

A glue specification has a halfword reference count in its first word, representing *null* plus the number of glue nodes that point to it (less one).
Note that the reference count appears in the same position as the *link* field in list nodes; this is the field that is initialized to *null* when a node is allocated, and it is also the field that is flagged by *EMPTY_FLAG* in empty nodes.

Glue specifications also contain three *scaled* fields, for the *width*, *stretch*, and *shrink* dimensions. Finally, there are two one-byte fields called *stretch_order* and *shrink_order*; these contain the orders of infinity (*NORMAL*, *FIL*, *FILL*, or *FILLL*) corresponding to the stretch and shrink values.

```c include/constants.h
#define GLUE_SPEC_SIZE 4 // number of words to allocate for a glue specification
#define FIL            1 // first-order infinity
#define FILL           2 // second-order infinity
#define FILLL          3 // third-order infinity
```

```c include/datastructures.h
#define glue_ref_count(X) link((X))       // reference count of a glue specification
#define stretch(X)        mem[(X) + 2].sc // the stretchability of this glob of glue
#define shrink(X)         mem[(X) + 3].sc // the shrinkability of this glob of glue
#define stretch_order     type            // order of infinity for stretching
#define shrink_order      subtype         // order of infinity for shrinking
```
