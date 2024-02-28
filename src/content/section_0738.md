# Section 738

Slants are not considered when placing accents in math mode.
The accenter is centered over the accentee, and the accent width is treated as zero with respect to the size of the final box.

```c << Declare math construction procedures >>+=
void make_math_accent(pointer q) {
    pointer p, x, y;        // temporary registers for box construction
    int a;                  // address of lig/kern instruction
    quarterword c;          // accent character
    internal_font_number f; // its font
    memory_word i;          // its |char_info|
    scaled s;               // amount to skew the accent to the right
    scaled h;               // height of character being accented
    scaled delta;           // space to remove between accent and accentee
    scaled w;               // width of the accentee, not including sub/superscripts
    
    fetch(accent_chr(q));
    if (char_exists(cur_i)) {
        i = cur_i;
        c = cur_c;
        f = cur_f;
        // << Compute the amount of skew >>
        x = clean_box(nucleus(q), cramped_style(cur_style));
        w = width(x);
        h = height(x);
        // << Switch to a larger accent if available and appropriate >>
        if (h < x_height(f)) {
            delta = h;
        }
        else {
            delta = x_height(f);
        }
        if ((math_type(supscr(q)) != EMPTY || math_type(subscr(q)) != EMPTY)
            && math_type(nucleus(q)) == MATH_CHAR)
        {
            // << Swap the subscript and superscript into box |x| >>
        }
        y = char_box(f, c);
        shift_amount(y) = s + half(w - width(y));
        width(y) = 0;
        p = new_kern(-delta);
        link(p) = x;
        link(y) = p;
        y = vpack(y, NATURAL);
        width(y) = width(x);
        if (height(y) < h) {
            // << Make the height of box |y| equal to |h| >>
        }
        info(nucleus(q)) = y;
        math_type(nucleus(q)) = SUB_BOX;
    }
}
```
