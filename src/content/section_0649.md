# Section 649

Here now is *hpack*, which contains few if any surprises.

```c builder/packaging.c
// << Start file |packaging.c| >>

pointer hpack(pointer p, scaled w, small_number m) {
    pointer r;              // the box node that will be returned
    pointer q;              // trails behind |p|
    scaled h, d, x;         // height, depth, and natural width
    scaled s;               // shift amount
    pointer g;              // points to a glue specification
    int o;                  // order of infinity
    internal_font_number f; // the font in a |CHAR_NODE|
    memory_word i;          // font information about a |CHAR_NODE|
    eight_bits hd;          // height and depth indices for a character
    
    last_badness = 0;
    r = get_node(BOX_NODE_SIZE);
    type(r) = HLIST_NODE;
    subtype(r) = MIN_QUARTERWORD;
    shift_amount(r) = 0;
    q = r + LIST_OFFSET;
    link(q) = p;
    h = 0;
    // << Clear dimensions to zero >>
    while (p != null) {
        // << Examine node |p| in the hlist, taking account of its effect on the dimensions of the new box, or moving it to the adjustment list; then advance |p| to the next node >>
    }
    if (adjust_tail != null) {
        link(adjust_tail) = null;
    }
    height(r) = h;
    depth(r) = d;
    // << Determine the value of |width(r)| and the appropriate glue setting; then |return| or |goto common_ending| >>
common_ending:
    // << Finish issuing a diagnostic message for an overfull or underfull hbox >>
    return r;
}
```
