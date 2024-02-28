# Section 114

When debugging, we may want to print a *memory_word* without knowing what type it is; so we print it in all modes.

```c io/basic_printing.c
#ifdef DEBUG
// prints |w| in all ways
void print_word(memory_word w) {
    print_int(w.integer);
    print_char(' ');
    print_scaled(w.sc);
    print_char(' ');
    print_scaled((scaled)round(w.gr * UNITY));
    print_ln();
    print_int(hh_lh(w));
    print_char('=');
    print_int(hh_b0(w));
    print_char(':');
    print_int(hh_b1(w));
    print_char(';');
    print_int(hh_rh(w));
    print_char(' ');
    print_int(qqqq_b0(w));
    print_char(':');
    print_int(qqqq_b1(w));
    print_char(':');
    print_int(qqqq_b2(w));
    print_char(':');
    print_int(qqqq_b3(w));
}
#endif
```
