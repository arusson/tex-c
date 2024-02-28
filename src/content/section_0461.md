# Section 461

The final member of $\TeX$'s value-scanning trio is *scan_glue*, which makes *cur_val* point to a glue specification.
The reference count of that glue spec will take account of the fact that *cur_val* is pointing to it.

The *level* parameter should be either *GLUE_VAL* or *MU_VAL*.

Since *scan_dimen* was so much more complex than *scan_int*, we might expect *scan_glue* to be even worse.
But fortunately, it is very simple, since most of the work has already been done.

```c parser/subroutines.c
// sets |cur_val| to a glue spec pointer
void scan_glue(small_number level) {
    bool negative; // should the answer be negated?
    pointer q;     // new glue specification
    bool mu;       // does |level = MU_VAL|?

    mu = (level == MU_VAL);
    // << Get the next non-blank non-sign token; set |negative| appropriately >>
    if (cur_cmd >= MIN_INTERNAL && cur_cmd <= MAX_INTERNAL) {
        scan_something_internal(level, negative);
        if (cur_val_level >= GLUE_VAL) {
            if (cur_val_level != level) {
                mu_error();
            }
            return;
        }
        if (cur_val_level == INT_VAL) {
            scan_dimen(mu, false, true);
        }
        else if (level == MU_VAL) {
            mu_error();
        }
    }
    else {
        back_input();
        scan_dimen(mu, false, false);
        if (negative) {
            negate(cur_val);
        }
    }
    // << Create a new glue specification whose width is |cur_val|; scan for its stretch and shrink components >>
}
```
