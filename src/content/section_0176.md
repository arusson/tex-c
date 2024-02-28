# Section 176

The *show_node_list* routine requires some auxiliary subroutines:
one to print a font-and-character combination, one to print a token list without its reference count, and one to print a rule dimension.

```c io/display_boxes.c
// prints |CHAR_NODE| data
void print_font_and_char(int p) {
    if (p > mem_end) {
        print_esc("CLOBBERED.");
    }
    else {
        if (/* font(p) < FONT_BASE || */ font(p) > FONT_MAX) {
            // |FONT_BASE = 0| and |font(p)| is in [0 .. 65535]
            print_char('*');
        }
        else {
            // << Print the font identifier for |font(p)| >>
        }
        print_char(' ');
        print_strnumber(character(p));
    }
}

// prints token list data in braces
void print_mark(int p) {
    print_char('{');
    if (p < hi_mem_min || p > mem_end) {
        print_esc("CLOBBERED.");
    }
    else {
        show_token_list(link(p), null, MAX_PRINT_LINE - 10);
    }
    print_char('}');
}

// prints dimension in rule node
void print_rule_dimen(scaled d) {
    if (is_running(d)) {
        print_char('*');
    }
    else {
        print_scaled(d);
    }
}
```
