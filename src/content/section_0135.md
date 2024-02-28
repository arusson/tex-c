# Section 135

An *HLIST_NODE* stands for a box that was made from a horizontal list.
Each *HLIST_NODE* is seven words long, and contains the following fields (in addition to the mandatory *type* and *link*, which we shall not mention explicitly when discussing the other node types):
The *height* and *width* and *depth* are scaled integers denoting the dimensions of the box.
There is also a *shift_amount* field, a scaled integer indicating how much this box should be lowered (if it appears in a horizontal list), or how much it should be moved to the right (if it appears in a vertical list).
There is a *list_ptr* field, which points to the beginning of the list from which this box was fabricated;
if *list_ptr* is *null*, the box is empty. Finally, there are three fields that represent the setting of the glue:
*glue_set(p)* is a word of type *glue_ratio* that represents the proportionality constant for glue setting;
*glue_sign(p)* is *STRETCHING* or *SHRINKING* or *NORMAL* depending on whether or not the glue should stretch or shrink or remain rigid;
and *glue_order(p)* specifies the order of infinity to which glue setting applies (*NORMAL*,
*FIL*, *FILL*, or *FILLL*).
The *subtype* field is not used.

```c include/constants.h
#define HLIST_NODE    0 // |type| of hlist nodes
#define BOX_NODE_SIZE 7 // number of words to allocate for a box node
#define WIDTH_OFFSET  1 // position of |width| field in a box node
#define DEPTH_OFFSET  2 // position of |depth| field in a box node
#define HEIGHT_OFFSET 3 // position of |height| field in a box node
#define LIST_OFFSET   5 // position of |list_ptr| field in a box node
#define NORMAL        0 // the most common case when several cases are named
#define STRETCHING    1 // glue setting applies to the stretch components
#define SHRINKING     2 // glue setting applies to the shrink components
#define GLUE_OFFSET   6 // position of |glue_set| in a box node
```

```c include/datastructures.h
#define width(X)        mem[(X) + WIDTH_OFFSET].sc  // width of the box, in sp
#define depth(X)        mem[(X) + DEPTH_OFFSET].sc  // depth of the box, in sp
#define height(X)       mem[(X) + HEIGHT_OFFSET].sc // height of the box, in sp
#define shift_amount(X) mem[(X) + 4].sc             // repositioning distance, in sp
#define list_ptr(X)     link((X) + LIST_OFFSET)     // beginning of the list inside the box
#define glue_order(X)   subtype((X) + LIST_OFFSET)  // applicable order of infinity
#define glue_sign(X)    type((X) + LIST_OFFSET)     // stretching or shrinking
#define glue_set(X)     mem[(X) + GLUE_OFFSET].gr   // a word of type |glue_ratio| for glue setting
```
