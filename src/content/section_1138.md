# Section 1138

```c math/math_lists.c
void init_math() {
    scaled w;               // new or partial |pre_display_size|
    scaled l = 0;           // new |display_width|
    scaled s = 0;           // new |display_indent|
    pointer p;              // current node when calculating |pre_display_size|
    pointer q;              // glue specification when calculating |pre_display_size|
    internal_font_number f; // font in current |CHAR_NODE|
    int n;                  // scope of paragraph shape specification
    scaled v;               // |w| plus possible glue amount
    scaled d;               // increment to |v|
    
    get_token(); // |get_x_token| would fail on \ifmmode!
    if (cur_cmd == MATH_SHIFT && mode > 0) {
        // << Go into display math mode >>
    }
    else {
        back_input();
        // << Go into ordinary math mode >>
    }
}
```
