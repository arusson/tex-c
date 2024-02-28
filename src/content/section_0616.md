# Section 616

The actual distances by which we want to move might be computed as the sum of several separate movements.
For example, there might be several glue nodes in succession, or we might want to move right by the width of some box plus some amount of glue.
More importantly, the baselineskip distances are computed in terms of glue together with the depth and height of adjacent boxes, and we want the `DVI` file to lump these three quantities together into a single motion.

Therefore, $\TeX$ maintains two pairs of global variables: *dvi_h* and *dvi_v* are the *h* and *v* coordinates corresponding to the commands actually output to the `DVI` file, while *cur_h* and *cur_v* are the coordinates corresponding to the current state of the output routines.
Coordinate changes will accumulate in *cur_h* and *cur_v* without being reflected in the output, until such a change becomes necessary or desirable; we can call the *movement* procedure whenever we want to make *dvi_h = cur_h* or *dvi_v = cur_v*.

The current font reflected in the `DVI` output is called *dvi_f*;
there is no need for a *'cur_f'* variable.

The depth of nesting of *hlist_out* and *vlist_out* is called *cur_s*;
this is essentially the depth of *PUSH* commands in the `DVI` output.

```c include/dvi.h
#define synch_h                              \
    do {                                     \
        if (cur_h != dvi_h) {                \
            movement(cur_h - dvi_h, RIGHT1); \
            dvi_h = cur_h;                   \
        }                                    \
    } while (0)


#define synch_v                             \
    do {                                    \
        if (cur_v != dvi_v) {               \
            movement(cur_v - dvi_v, DOWN1); \
            dvi_v = cur_v;                  \
        }                                   \
    } while (0)
```

```c << Global variables >>+=
scaled dvi_h, dvi_v;        // a `DVI` reader program thinks we are here
scaled cur_h, cur_v;        // TeX thinks we are here
internal_font_number dvi_f; // the current font
int cur_s;                  // current depth of output box nesting, initially -1
```
