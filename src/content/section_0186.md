# Section 186

The code will have to change in this place if *glue_ratio* is a structured type instead of an ordinary *real*.
Note that this routine should avoid arithmetic errors even if the *glue_set* field holds an
arbitrary random value.
The following code assumes that a properly formed nonzero *real* number has absolute value $2^{20}$ or more when it is regarded as an integer; this precaution was adequate to prevent floating point underflow on the author's computer.

> ![NOTE]
> The precaution has been removed.

```c << Display the value of |glue_set(p)| >>=
g = glue_set(p);
if (g != 0.0 && glue_sign(p) != NORMAL) {
    print(", glue set ");
    if (glue_sign(p) == SHRINKING) {
        print("- ");
    }
    /* if (abs(mem[p + GLUE_OFFSET].integer) < 0x100000) {
        print("?.?");
    } */
    if (abs(g) > 20000.0) {
        if (g > 0.0) {
            print_char('>');
        }
        else {
            print("< -");
        }
        print_glue(20000*UNITY, glue_order(p), "");
    }
    else {
        print_glue((scaled)round(UNITY*g), glue_order(p), "");
    }
}
```
