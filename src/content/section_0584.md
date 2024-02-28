# Section 584

The `DVI` format is intended to be both compact and easily interpreted by a machine.
Compactness is achieved by making most of the information implicit instead of explicit.
When a `DVI`-reading program reads the commands for a page, it keeps track of several quantities:
(a)&nbsp;The current font *f* is an integer; this value is changed only by *FNT* and *FNT_NUM* commands.
(b)&nbsp;The current position on the page is given by two numbers called the horizontal and vertical coordinates, *h* and *v*.
Both coordinates are zero at the upper left corner of the page;
moving to the right corresponds to increasing the horizontal coordinate, and moving down corresponds to increasing the vertical coordinate.
Thus, the coordinates are essentially Cartesian, except that vertical directions are flipped; the Cartesian version of *(h, v)* would be *(h, −v)*.
(c)&nbsp;The current spacing amounts are given by four numbers *w*, *x*, *y*, and *z*, where *w* and&nbsp;*x* are used for horizontal spacing and where *y* and&nbsp;*z* are used for vertical spacing.
(d)&nbsp;There is a stack containing *(h, v, w, x, y, z)* values; the `DVI` commands *PUSH* and *POP* are used to change the current level of operation.
Note that the current font&nbsp;*f* is not pushed and popped; the stack contains only information about positioning.

The values of *h*, *v*, *w*, *x*, *y*, and *z* are signed integers having up to 32 bits, including the sign.
Since they represent physical distances, there is a small unit of measurement such that increasing *h* by&nbsp;1 means moving a certain tiny distance to the right.
The actual unit of measurement is variable, as explained below; $\TeX$ sets things up so that its `DVI` output is in sp units, i.e., scaled points, in agreement with all the *scaled* dimensions in $\TeX$'s data structures.
