# Section 174

Boxes, rules, inserts, whatsits, marks, and things in general that are sort of "complicated" are indicated only by printing '`[]`'.

```c io/display_boxes.c
// << Start file |display_boxes.c| >>=

// prints highlights of list |p|
void short_display(int p) {
    int n; // for replacement counts
    while (p > MEM_MIN) {
        if (is_char_node(p)) {
            if (p <= mem_end) {
                if (font(p) != font_in_short_display) {
                    if (/* font(p) < FONT_BASE || */ font(p) > FONT_MAX) {
                        // Comparison with |FONT_BASE| is useless
                        // since |FONT_BASE = 0| and |font(p)| is in [0 .. 65535]
                        print_char('*');
                    }
                    else {
                        // << Print the font identifier for |font(p)| >>
                    }
                    print_char(' ');
                    font_in_short_display = font(p);
                }
                print_strnumber(character(p));
            }
        }
        else {
            // << Print a short indication of the contents of node |p| >>
        }
        p = link(p);
    }
}
```
