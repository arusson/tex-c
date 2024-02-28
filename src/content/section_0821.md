# Section 821

The passive node for a given breakpoint contains only four fields:

- *link* points to the passive node created just before this one,
  if any, otherwise it is *null*.

- *cur_break* points to the position of this breakpoint in the
  horizontal list for the paragraph being broken.

- *prev_break* points to the passive node that should precede this
  one in an optimal path to this breakpoint.

- *serial* is equal to *n* if this passive node is the *n*th
  one created during the current pass. (This field is used only when 
  printing out detailed statistics about the line-breaking calculations.)

There is a global variable called *passive* that points to the most recently created passive node.
Another global variable, *printed_node*, is used to help print out the paragraph when detailed information about the line-breaking computation is being displayed.

```c include/constants.h
#define PASSIVE_NODE_SIZE 2 // number of words in passive nodes
```

```c include/breaker.h
#define cur_break  rlink // in passive node, points to position of this breakpoint
#define prev_break llink // points to passive node that should precede this one
#define serial     info  // serial number for symbolic identification
```

```c << Global variables >>+=
pointer passive;      // most recent node on passive list
pointer printed_node; // most recent node that has been printed
halfword pass_number; // the number of passive nodes allocated on this pass
```
