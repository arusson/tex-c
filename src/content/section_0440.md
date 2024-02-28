# Section 440

The *scan_int* routine is used also to scan the integer part of a fraction;
for example, the '`3`' in '`3.14159`' will be found by *scan_int*.
The *scan_dimen* routine assumes that *cur_tok = POINT_TOKEN* after the integer part of such a fraction has been scanned by *scan_int*, and that the decimal point has been backed up to be scanned again.

```c parser/subroutines.c
// sets |cur_val| to an integer
void scan_int() {
    bool negative;  // should the answer be negated?
    int m;          // |2^{31} / radix|, the threshold of danger
    small_number d; // the digit just scanned
    bool vacuous;   // have no digits appeared?
    bool ok_so_far; // has an error message been issued?

    radix = 0;
    ok_so_far = true;
    // << Get the next non-blank non-sign token; set |negative| appropriately >>
    if (cur_tok == ALPHA_TOKEN) {
        // << Scan an alphabetic character code into |cur_val| >>
    }
    else if (cur_cmd >= MIN_INTERNAL && cur_cmd <= MAX_INTERNAL) {
        scan_something_internal(INT_VAL, false);
    }
    else {
        // << Scan a numeric constant >>
    }
    if (negative) {
        negate(cur_val);
    }
}
```
