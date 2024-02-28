# Section 155

A *KERN_NODE* has a *width* field to specify a (normally negative) amount of spacing.
This spacing correction appears in horizontal lists between letters like A and V when the font designer said that it looks better to move them closer together or further apart.
A kern node can also appear in a vertical list, when its *'width'* denotes additional spacing in the vertical direction.
The *subtype* is either *NORMAL* (for kerns inserted from font information or math mode calculations) or *EXPLICIT* (for kerns inserted from `\kern` and `\/` commands) or *ACC_KERN* (for kerns inserted from non-math accents) or *MU_GLUE* (for kerns inserted from `\mkern` specifications in math formulas).

```c include/constants.h
#define KERN_NODE 11 // |type| of a kern node
#define EXPLICIT  1  // |subtype| of kern nodes from \kern and \/
#define ACC_KERN  2  // |subtype| of kern nodes from accents
```
