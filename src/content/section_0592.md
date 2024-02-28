# Section 592: Shipping pages out

After considering $\TeX$'s eyes and stomach, we come now to the bowels.

The *ship_out* procedure is given a pointer to a box; its mission is to describe that box in `DVI` form, outputting a "page" to *dvi_file*.
The `DVI` coordinates *(h,v) = (0,0)* should correspond to the upper left corner of the box being shipped.

Since boxes can be inside of boxes inside of boxes, the main work of *ship_out* is done by two mutually recursive routines, *hlist_out* and *vlist_out*, which traverse the hlists and vlists inside of horizontal and vertical boxes.

As individual pages are being processed, we need to accumulate information about the entire set of pages, since  statistics must be reported in the postamble.
The global variables *total_pages*, *max_v*, *max_h*, *max_push*, and *last_bop* are used to record this information.

The variable *doing_leaders* is *true* while leaders are being output.
The variable *dead_cycles* contains the number of times an output routine has been initiated since the last *ship_out*.

A few additional global variables are also defined here for use in *vlist_out* and *hlist_out*.
They could have been local variables, but that would waste stack space when boxes are deeply nested, since the values of these variables are not needed during recursive calls.

```c << Global variables >>+=
int total_pages;    // the number of pages that have been shipped out
scaled max_v;       // maximum height-plus-depth of pages shipped so far
scaled max_h;       // maximum width of pages shipped so far
int max_push;       // deepest nesting of |PUSH| commands encountered so far
int last_bop;       // location of previous |BOP| in the `DVI` output
int dead_cycles;    // recent outputs that didn't ship anything out
bool doing_leaders; // are we inside a leader box?

quarterword c, f;                 // character and font in current |CHAR_NODE|
scaled rule_ht, rule_dp, rule_wd; // size of current rule being output
pointer g;                        // current glue specification
int lq, lr;                       // quantities used in calculations for leaders
```
