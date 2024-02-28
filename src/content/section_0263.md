# Section 263

Here is a similar procedure; it avoids the error checks, and it never prints a space after the control sequence.

```c io/basic_printing.c
// prints a control sequence
void sprint_cs(pointer p) {
    if (p < HASH_BASE) {
        if (p < SINGLE_BASE) {
            print_strnumber(p - ACTIVE_BASE);
        }
        else if (p < NULL_CS) {
            print_esc_strnumber(p - SINGLE_BASE);
        }
        else {
            print_esc("csname");
            print_esc("endcsname");
        }
    }
    else {
        print_esc_strnumber(text(p));
    }
}
```
