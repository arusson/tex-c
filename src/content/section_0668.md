# Section 668

The *vpack* subroutine is actually a special case of a slightly more general routine called *vpackage*, which has four parameters.
The fourth parameter, which is *MAX_DIMEN* in the case of *vpack*, specifies the maximum depth of the page box that is constructed.
The depth is first computed by the normal rules; if it exceeds this limit, the reference point is simply moved down until the limiting depth is attained.

```c include/builder.h
// special case of unconstrained depth
#define vpack(...) vpackage(__VA_ARGS__, MAX_DIMEN) 
```

```c builder/packaging.c
pointer vpackage(pointer p, scaled h, small_number m, scaled l) {
    pointer r;      // the box node that will be returned
    scaled w, d, x; // width, depth, and natural height
    scaled s;       // shift amount
    pointer g;      // points to a glue specification
    int o;          // order of infinity
    
    last_badness = 0;
    r = get_node(BOX_NODE_SIZE);
    type(r) = VLIST_NODE;
    subtype(r) = MIN_QUARTERWORD;
    shift_amount(r) = 0;
    list_ptr(r) = p;
    w = 0;
    // << Clear dimensions to zero >>
    while (p != null) {
        // << Examine node |p| in the vlist, taking account of its effect on the dimensions of the new box; then advance |p| to the next node >>
    }
    width(r) = w;
    if (d > l) {
        x = x + d - l;
        depth(r) = l;
    }
    else {
        depth(r) = d;
    }
    // << Determine the value of |height(r)| and the appropriate glue setting; then |return| or |goto common_ending| >>

common_ending:
    // << Finish issuing a diagnostic message for an overfull or underfull vbox >>
    return r;
}
```
