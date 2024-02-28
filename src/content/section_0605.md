# Section 605

In order to implement such an idea, $\TeX$ maintains a stack of pointers to the *DOWN*, *Y*, and *Z* commands that have been generated for the current page.
And there is a similar stack for *RIGHT*, *W*, and *X* commands.
These stacks are called the down stack and right stack, and their top elements are maintained in the variables *down_ptr* and *right_ptr*.

Each entry in these stacks contains four fields:
The *width* field is the amount of motion down or to the right; the *location* field is the byte number of the `DVI` command in question (including the appropriate *dvi_offset*); the *link* field points to the next item below this one on the stack; and the *info* field encodes the options for possible change in the `DVI` command.

```c include/constants.h
#define MOVEMENT_NODE_SIZE 3 // number of words per entry in the down and right stacks
```

```c include/dvi.h
#define location(X) mem[(X) + 2].integer // `DVI` byte number for a movement command
```

```c << Global variables >>+=
pointer down_ptr, right_ptr; // heads of the down and right stacks
```
