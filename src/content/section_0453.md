# Section 453

Now comes the harder part:
At this point in the program, *cur_val* is a nonnegative integer and $f/2^{16}$ is a nonnegative fraction less than 1;
we want to multiply the sum of these two quantities by the appropriate factor, based on the specified units, in order to produce a *scaled* result, and we want to do the calculation with fixed point arithmetic that does not overflow.

```c << Scan units and set |cur_val| to x * (|cur_val| + f/2^{16}), where there are |x| sp per unit; |goto attach_sign| if the units are internal >>=
if (inf) {
    // << Scan for |fil| units; |goto attach_fraction| if found >>
}

// << Scan for units that are internal dimensions; |goto attach_sign| with |cur_val| set if found >>

if (mu) {
    // << Scan for mu units and |goto attach_fraction| >>
}
if (scan_keyword("true")) {
    // << Adjust for the magnification ratio >>
}
if (scan_keyword("pt")) {
    goto attach_fraction; // the easy case
}

// << Scan for all other units and adjust |cur_val| and |f| accordingly; |goto done| in the case of scaled points >>

attach_fraction:
if (cur_val >= 0x4000) {
    arith_error = true;
}
else {
    cur_val = cur_val * UNITY + f;
}
done:
```
