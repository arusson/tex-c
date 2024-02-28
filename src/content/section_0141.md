# Section 141

A *MARK_NODE* has a *mark_ptr* field that points to the reference count of a token list that contains the user's `\mark` text.
This field occupies a full word instead of a halfword, because there's nothing to put in the other halfword; it is easier in Pascal to use the full word than to risk leaving garbage in the unused half.

```c include/constants.h
#define MARK_NODE       4 // |type| of a mark node
#define SMALL_NODE_SIZE 2 // number of words to allocate for most node types
```

```c include/datastructures.h
#define mark_ptr(X) mem[(X) + 1].integer // head of the token list for a mark
```
