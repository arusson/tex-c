# Section 706

The *var_delimiter* function, which finds or constructs a sufficiently large delimiter, is the most interesting of the auxiliary functions that currently concern us.
Given a pointer *d* to a delimiter field in some noad, together with a size code *s* and a vertical distance *v*, this function returns a pointer to a box that contains the smallest variant of *d* whose height plus depth is *v* or more.
(And if no variant is large enough, it returns the largest available variant.) In particular, this routine will construct arbitrarily large delimiters from extensible components, if *d* leads to such characters.

The value returned is a box whose *shift_amount* has been set so that the box is vertically centered with respect to the axis in the given size.
If a built-up symbol is returned, the height of the box before shifting will be the height of its topmost component.

```c math/math_subroutines.c
// << Declare subprocedures for |var_delimiter| >>

pointer var_delimiter(pointer d, small_number s, scaled v) {
    pointer b;                 // the box that will be constructed
    internal_font_number f, g; // best-so-far and tentative font codes
    quarterword c, x, y;       // best-so-far and tentative character codes
    int m, n;                  // the number of extensible pieces
    scaled u;                  // height-plus-depth of a tentative character
    scaled w;                  // largest height-plus-depth so far
    memory_word q;             // character info
    eight_bits hd;             // height-depth byte
    memory_word r;             // extensible pieces
    small_number z;            // runs through font family members
    bool large_attempt;        // are we trying the "large" variant?
    
    c = 0;
    f = NULL_FONT;
    w = 0;
    large_attempt = false;
    z = small_fam(d);
    x = small_char(d);
    while(true) {
        // << Look at the variants of |(z, x)|; set |f| and |c| whenever a better character is found; |goto found| as soon as a large enough variant is encountered >>
        if (large_attempt) {
            goto found; // there were none large enough
        }
        large_attempt = true;
        z = large_fam(d);
        x = large_char(d);
    }
found:
    if (f != NULL_FONT) {
        // << Make variable |b| point to a box for |(f, c)| >>
    }
    else {
        b = new_null_box();
        width(b) = null_delimiter_space; // use this width if no delimiter was found
    }
    shift_amount(b) = half(height(b) - depth(b)) - axis_height(s);
    return b;
}
```
