# Section 124

The available-space list that keeps track of the variable-size portion of *mem* is a nonempty, doubly-linked circular list of empty nodes, pointed to by the roving pointer *rover*.

Each empty node has size 2 or more; the first word contains the special value *MAX_HALFWORD* in its *link* field and the size in its *info* field;
the second word contains the two pointers for double linking.

Each nonempty node also has size 2 or more.
Its first word is of type *two_halves*, and its *link* field is never equal to *MAX_HALFWORD*.
Otherwise there is complete flexibility with respect to the contents of its other fields and its other words.

(We require *MEM_MAX* $<$ *MAX_HALFWORD* because terrible things can happen when *MAX_HALFWORD* appears in the *link* field of a nonempty node.)

```c include/constants.h
#define EMPTY_FLAG MAX_HALFWORD // the |link| of an empty variable-size node
```

```c include/datastructures.h
#define is_empty(X) (link((X)) == EMPTY_FLAG) // tests for empty node
#define node_size   info          // the size field in empty variable-size nodes
#define llink(X)    info((X) + 1) // left link in doubly-linked list of empty nodes
#define rlink(X)    link((X) + 1) // right link in doubly-linked list of empty nodes
```

```c << Global variables >>+=
pointer rover; // points to some node in the list of empties
```
