# Section 756

The purpose of *make_scripts(q, delta)* is to attach the subscript and/or superscript of noad *q* to the list that starts at *new_hlist(q)*, given that the subscript and superscript aren't both empty.
The superscript will appear to the right of the subscript by a given distance *delta*.

We set *shift_down* and *shift_up* to the minimum amounts to shift the baseline of subscripts and superscripts based on the given nucleus.

```c << Declare math construction procedures >>+=
void make_scripts(pointer q, scaled delta) {
    pointer p, x, y, z;               // temporary registers for box construction
    scaled shift_up, shift_down, clr; // dimensions in the calculation
    small_number t;                   // subsidiary size code
    
    p = new_hlist(q);
    if (is_char_node(p)) {
        shift_up = 0;
        shift_down = 0;
    }
    else {
        z = hpack(p, NATURAL);
        if (cur_style < SCRIPT_STYLE) {
            t = SCRIPT_SIZE;
        }
        else {
            t = SCRIPT_SCRIPT_SIZE;
        }
        shift_up = height(z) - sup_drop(t);
        shift_down = depth(z) + sub_drop(t);
        free_node(z, BOX_NODE_SIZE);
    }
    if (math_type(supscr(q)) == EMPTY) {
        // << Construct a subscript box |x| when there is no superscript >>
    }
    else {
        // << Construct a superscript box |x| >>
        if (math_type(subscr(q)) == EMPTY) {
            shift_amount(x) = -shift_up;
        }
        else {
            // << Construct a sub/superscript combination box |x|, with the superscript offset by |delta| >>
        }
    }
    if (new_hlist(q) == null) {
        new_hlist(q) = x;
    }
    else {
        p = new_hlist(q);
        while (link(p) != null) {
            p = link(p);
        }
        link(p) = x;
    }
}
```
