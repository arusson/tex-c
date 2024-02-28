# Section 178

The next subroutine prints a whole glue specification.

```c io/display_boxes.c
// prints a glue specification
void print_spec(int p, char *s) {
    if (p < MEM_MIN || p >= lo_mem_max) {
        print_char('*');
    }
    else {
        print_scaled(width(p));
        if (strlen(s) != 0) {
            print(s);
        }
        if (stretch(p) != 0) {
            print(" plus ");
            print_glue(stretch(p), stretch_order(p), s);
        }
        if (shrink(p) != 0) {
            print(" minus ");
            print_glue(shrink(p), shrink_order(p), s);
        }
    }
}
```
