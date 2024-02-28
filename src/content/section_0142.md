# Section 142

An *ADJUST_NODE*, which occurs only in horizontal lists, specifies material that will be moved out into the surrounding vertical list; i.e., it is used to implement $\TeX$'s '`\vadjust`'
operation.
The *adjust_ptr* field points to the vlist containing this material.

```c include/constants.h
#define ADJUST_NODE 5 // |type| of an adjust node
```

```c include/datastructures.h
#define adjust_ptr mark_ptr // vertical list to be moved out of horizontal list
```
