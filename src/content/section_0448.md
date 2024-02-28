# Section 448

Constructions like '`-'77 pt`' are legal dimensions, so *scan_dimen* may begin with *scan_int*.
This explains why it is convenient to use *scan_int* also for the integer part of a decimal fraction.

Several branches of *scan_dimen* work with *cur_val* as an integer and with an auxiliary fraction $f$, so that the actual quantity of interest is *cur_val* + $f/2^{16}$.
At the end of the routine, this "unpacked" representation is put into the single word *cur_val*, which suddenly switches significance from *int* to *scaled*.

```c include/parser.h
#define scan_normal_dimen scan_dimen(false, false, false)
```

```c parser/subroutines.c
// sets |cur_val| to a dimension
void scan_dimen(bool mu, bool inf, bool shortcut) {
    bool negative; // should the answer be negated?
    int f;         // numerator of a fraction whose denominator is $2^{16}$
    // << Local variables for dimension calculations >>
    
    f = 0;
    arith_error = false;
    cur_order = NORMAL;
    negative = false;
    if (!shortcut) {
        // << Get the next non-blank non-sign token; set |negative| appropriately >>
        if (cur_cmd >= MIN_INTERNAL && cur_cmd <= MAX_INTERNAL) {
            // << Fetch an internal dimension and |goto attach_sign|, or fetch an internal integer >>
        }
        else { 
            back_input();
            if (cur_tok == CONTINENTAL_POINT_TOKEN) {
                cur_tok = POINT_TOKEN;
            }
            if (cur_tok != POINT_TOKEN) {
                scan_int();
            }
            else {
                radix = 10;
                cur_val = 0;
            }
            if (cur_tok == CONTINENTAL_POINT_TOKEN) {
                cur_tok = POINT_TOKEN;
            }
            if (radix == 10 && cur_tok == POINT_TOKEN) {
                // << Scan decimal fraction >>
            }
        }
    }
    if (cur_val < 0) {
        // in this case |f = 0|
        negative = !negative;
        negate(cur_val);
    }
    
    // << Scan units and set |cur_val| to x * (|cur_val| + f/2^{16}), where there are |x| sp per unit; |goto attach_sign| if the units are internal >>
    
    // << Scan an optional space >>

attach_sign:
    if (arith_error || abs(cur_val) >= 0x40000000) {
        // << Report that this dimension is out of range >>
    }
    if (negative) {
        negate(cur_val);
    }
}
```
