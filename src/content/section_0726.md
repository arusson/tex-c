# Section 726

Here is the overall plan of *mlist_to_hlist*, and the list of its local variables.

> ![NOTE]
> The *MATH_SPACING* string is only used for *mlist_to_hlist* so it must be declared beforehand.
> Its value is given in section&nbsp;[764](#section-764).

```c math/math_typesetting.c
// << Declare math construction procedures >>

// << Declare |MATH_SPACING| for |mlist_to_hlist| >>

void mlist_to_hlist() {
    pointer mlist;           // beginning of the given list
    bool penalties;          // should penalty nodes be inserted?
    small_number style;      // the given style
    small_number save_style; // holds |cur_style| during recursion
    pointer q;               // runs through the mlist
    pointer r;               // the most recent noad preceding |q|
    small_number r_type;     // the |type| of noad |r|, or |OP_NOAD| if |r = null|
    small_number t;          // the effective |type| of noad |q| during the second pass
    pointer p, x, y, z;      // temporary registers for list construction
    int pen;                 // a penalty to be inserted
    small_number s;          // the size of a noad to be deleted
    scaled max_h, max_d;     // maximum height and depth of the list translated so far
    scaled delta;            // offset between subscript and superscript

    p = null;
    x = null;
    mlist = cur_mlist;
    penalties = mlist_penalties;
    style = cur_style; // tuck global parameters away as local variables
    q = mlist;
    r = null;
    r_type = OP_NOAD;
    max_h = 0;
    max_d = 0;
    // << Set up the values of |cur_size| and |cur_mu|, based on |cur_style| >>
    while (q != null) {
        // << Process node-or-noad |q| as much as possible in preparation for the second pass of |mlist_to_hlist|, then move to the next item in the mlist >>
    }
    // << Convert a final |BIN_NOAD| to an |ORD_NOAD| >>
    // << Make a second pass over the mlist, removing all noads and inserting the proper spacing and penalties >>
}
```
