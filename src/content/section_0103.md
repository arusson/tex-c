# Section 103

Conversely, here is a procedure analogous to *print_int*.
If the output of this procedure is subsequently read by $\TeX$ and converted by the *round_decimals* routine above, it turns out that the original value will be reproduced exactly;
the "simplest" such decimal number is output, but there is always at least one digit following the decimal point.

The invariant relation in the **repeat** loop is that a sequence of decimal digits yet to be printed will yield the original number if and only if they form a fraction $f$ in the range $s - \delta\leq 10\cdot2^{16}f < s$.
We can stop if and only if $f = 0$ satisfies this condition; the loop will terminate before $s$ can possibly become zero.

```c io/basic_printing.c
// prints scaled real, rounded to five digits
void print_scaled(scaled s) {
    scaled delta; // amount of allowable inaccuracy
    if (s < 0) {
        // print the sign, if negative
        print_char('-');
        negate(s);
    }
    print_int(s / UNITY); // print the integer part
    print_char('.');
    s = (s % UNITY)*10 + 5;
    delta = 10;
    do {
        if (delta > UNITY) {
            s += 32768 - 50000; // round the last digit
        }
        print_char('0' + (s / UNITY));
        s = 10 * (s % UNITY);
        delta *= 10;
    } while (s > delta);
}
```
