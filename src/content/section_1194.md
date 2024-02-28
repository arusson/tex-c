# Section 1194

```c math/math_lists.c
void after_math() {
    bool l;      // '\leqno' instead of '\eqno'
    bool danger; // not enough symbol fonts are present
    int m;       // |MMODE| or |-MMODE|
    pointer p;   // the formula
    pointer a;   // box containing equation number
    // << Local variables for finishing a displayed formula >>

    danger = false;
    // << Check that the necessary fonts for math symbols are present; if not, flush the current math lists and set |danger = true| >>
    m = mode;
    l = false;
    p = fin_mlist(null); // this pops the nest
    if (mode == -m) {
        // end of equation number
        // << Check that another $ follows >>
        cur_mlist = p;
        cur_style = TEXT_STYLE;
        mlist_penalties = false;
        mlist_to_hlist();
        a = hpack(link(TEMP_HEAD), NATURAL);
        unsave();
        decr(save_ptr); // now |cur_group = MATH_SHIFT_GROUP|
        if (saved(0) == 1) {
            l = true;
        }
        danger = false;
        // << Check that the necessary fonts for math symbols are present; if not, flush the current math lists and set |danger = true| >>
        m = mode;
        p = fin_mlist(null);
    }
    else {
        a = null;
    }
    if (m < 0) {
        // << Finish math in text >>
    }
    else {
        if (a == null) {
            // << Check that another $ follows >>
        }
        // << Finish displayed math >>
    }
}
```
