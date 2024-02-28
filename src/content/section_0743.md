# Section 743

The *make_fraction* procedure is a bit different because it sets *new_hlist(q)* directly rather than making a sub-box.

```c << Declare math construction procedures >>+=
void make_fraction(pointer q) {
    pointer p, v, x, y, z; // temporary registers for box construction
    scaled delta, delta1, delta2, shift_up, shift_down, clr; // dimensions for box calculations
    if (thickness(q) == DEFAULT_CODE) {
        thickness(q) = default_rule_thickness;
    }

    // << Create equal-width boxes |x| and |z| for the numerator and denominator, and compute the default amounts |shift_up| and |shift_down| by which they are displaced from the baseline >>

    if (thickness(q) == 0) {
        // << Adjust |shift_up| and |shift_down| for the case of no fraction line >>
    }
    else {
        // << Adjust |shift_up| and |shift_down| for the case of a fraction line >>
    }

    // << Construct a vlist box for the fraction, according to |shift_up| and |shift_down| >>

    // << Put the fraction into a box with its delimiters, and make |new_hlist(q)| point to it >>
}
```
