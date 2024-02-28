# Section 709

Here is a subroutine that creates a new box, whose list contains a single character, and whose width includes the italic correction for that character.
The height or depth of the box will be negative, if the height or depth of the character is negative;
thus, this routine may deliver a slightly different result than *hpack* would produce.

```c << Declare subprocedures for |var_delimiter| >>=
pointer char_box(internal_font_number f, quarterword c) {
    memory_word q;
    eight_bits hd; // |height_depth| byte
    pointer b, p;  // the new box and its character node
    q = char_info(f, c);
    hd = height_depth(q);
    b = new_null_box();
    width(b) = char_width(f, q) + char_italic(f, q);
    height(b) = char_height(f, hd);
    depth(b) = char_depth(f, hd);
    p = get_avail();
    character(p) = c;
    font(p) = f;
    list_ptr(b) = p;
    return b;
}
```
