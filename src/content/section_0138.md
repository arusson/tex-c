# Section 138

A *RULE_NODE* stands for a solid black rectangle; it has *width*, *depth*, and *height* fields just as in an *HLIST_NODE*.
However, if any of these dimensions is $-2^{30}$, the actual value will be determined by running the rule up to the boundary of the innermost enclosing box.
This is called a "running dimension".
The *width* is never running in an hlist; the *height* and *depth* are never running in a vlist.

```c include/constants.h
#define RULE_NODE 2           // |type| of rule nodes
#define RULE_NODE_SIZE 4      // number of words to allocate for a rule node
#define NULL_FLAG -0x40000000 // -2^{30}, signifies a missing item
```

```c include/datastructures.h
#define is_running(X) ((X) == NULL_FLAG) // tests for a running dimension
```
