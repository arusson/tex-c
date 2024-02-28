# Section 749

If the nucleus of an *OP_NOAD* is a single character, it is to be centered vertically with respect to the axis, after first being enlarged (via a character list in the font) if we are in display style.
The normal convention for placing displayed limits is to put them above and below the operator in display style.

The italic correction is removed from the character if there is a subscript and the limits are not being displayed.
The *make_op* routine returns the value that should be used as an offset between subscript and superscript.

After *make_op* has acted, *subtype(q)* will be *LIMITS* if and only if the limits have been set above and below the operator.
In that case, *new_hlist(q)* will already contain the desired final box.

```c << Declare math construction procedures >>+=
scaled make_op(pointer q) {
    scaled delta;          // offset between subscript and superscript
    pointer p, v, x, y, z; // temporary registers for box construction
    quarterword c;         // registers for character examination
    memory_word i;               
    scaled shift_up, shift_down; // dimensions for box calculation
    
    if (subtype(q) == NORMAL && cur_style < TEXT_STYLE) {
        subtype(q) = LIMITS;
    }
    if (math_type(nucleus(q)) == MATH_CHAR) {
        fetch(nucleus(q));
        if (cur_style < TEXT_STYLE && char_tag(cur_i) == LIST_TAG) {
            // make it larger
            c = rem_byte(cur_i);
            i = char_info(cur_f, c);
            if (char_exists(i)) {
                cur_c = c;
                cur_i = i;
                character(nucleus(q)) = c;
            }
        }
        delta = char_italic(cur_f, cur_i);
        x = clean_box(nucleus(q), cur_style);
        if (math_type(subscr(q)) != EMPTY && subtype(q) != LIMITS) {
            // remove italic correction
            width(x) -= delta;
        }
        // center vertically
        shift_amount(x) = half(height(x) - depth(x)) - axis_height(cur_size);
        math_type(nucleus(q)) = SUB_BOX;
        info(nucleus(q)) = x;
    }
    else {
        delta = 0;
    }
    if (subtype(q) == LIMITS) {
        // << Construct a box with limits above and below it, skewed by |delta| >>
    }
    return delta;
}
```
