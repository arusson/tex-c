# Section 1123

The positioning of accents is straightforward but tedious.
Given an accent of width *a*, designed for characters of height *x* and slant *s*;
and given a character of width *w*, height *h*, and slant *t*:
We will shift the accent down by *x − h*, and we will insert kern nodes that have the effect of centering the accent over the character and shifting the accent to the
right by $\delta$ = ${1\over2}$(*w* − *a*) + *h* $\cdot$ *t* − *x* $\cdot$ *s*.
If either character is absent from the font, we will simply use the other, without shifting.

```c builder/boxes_and_lists.c
void make_accent() {
    double s, t;              // amount of slant
    pointer p, q, r;          // character, box, and kern nodes
    internal_font_number f;   // relevant font
    scaled a, h, x, w, delta; // heights and widths, as explained above
    memory_word i;            // character information
    
    scan_char_num();
    f = cur_font;
    p = new_character(f, cur_val);
    if (p != null) {
        x = x_height(f);
        s = slant(f) / 65536.0;
        a = char_width(f, char_info(f, character(p)));
        do_assignments();
        // << Create a character node |q| for the next character, but set |q = null| if problems arise >>
        if (q != null) {
            // << Append the accent with appropriate kerns, then set |p = q| >>
        }
        link(tail) = p;
        tail = p;
        space_factor = 1000;
    }
}
```
