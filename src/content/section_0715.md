# Section 715

The next subroutine is much simpler; it is used for numerators and denominators of fractions as well as for displayed operators and their limits above and below.
It takes a given box&nbsp;*b* and changes it so that the new box is centered in a box of width&nbsp;*w*.
The centering is done by putting `\hss` glue at the left and right of the list inside *b*, then packaging the new box; thus, the actual box might not really be centered, if it already contains infinite glue.

The given box might contain a single character whose italic correction has been added to the width of the box; in this case a compensating kern is inserted.

```c math/math_subroutines.c
pointer rebox(pointer b, scaled w) {
    pointer p;              // temporary register for list manipulation
    internal_font_number f; // font in a one-character box
    scaled v;               // width of a character without italic correction
    
    if (width(b) != w && list_ptr(b) != null) {
        if (type(b) == VLIST_NODE) {
            b = hpack(b, NATURAL);
        }
        p = list_ptr(b);
        if (is_char_node(p) && link(p) == null) {
            f = font(p);
            v = char_width(f, char_info(f, character(p)));
            if (v != width(b)) {
                link(p) = new_kern(width(b) - v);
            }
        }
        free_node(b, BOX_NODE_SIZE);
        b = new_glue(SS_GLUE);
        link(b) = p;
        while (link(p) != null) {
            p = link(p);
        }
        link(p) = new_glue(SS_GLUE);
        return hpack(b, w, EXACTLY);
    }
    else {
        width(b) = w;
        return b;
    }
}
```
