# Section 1113

```c builder/boxes_and_lists.c
void append_italic_correction() {
    pointer p;              // |CHAR_NODE| at the tail of the current list
    internal_font_number f; // the font in the |CHAR_NODE|
    if (tail != head) {
        if (is_char_node(tail)) {
            p = tail;
        }
        else if (type(tail) == LIGATURE_NODE) {
            p = lig_char(tail);
        }
        else {
            return;
        }
        f = font(p);
        tail_append(new_kern(char_italic(f, char_info(f, character(p)))));
        subtype(tail) = EXPLICIT;
    }
}
```
