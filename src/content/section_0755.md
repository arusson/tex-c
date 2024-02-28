# Section 755

```c << Create a character node |p| for |nucleus(q)|, possibly followed by a kern node for the italic correction, and set |delta| to the italic correction if a subscript is present >>=
fetch(nucleus(q));
if (char_exists(cur_i)) {
    delta = char_italic(cur_f, cur_i);
    p = new_character(cur_f, cur_c);
    if (math_type(nucleus(q)) == MATH_TEXT_CHAR && space(cur_f) != 0) {
        // no italic correction in mid-word of text font
        delta = 0;
    }
    if (math_type(subscr(q)) == EMPTY && delta != 0) {
        link(p) = new_kern(delta);
        delta = 0;
    }
}
else {
    p = null;
}
```
