# Section 65

The following procedure, which prints out the decimal representation of a given integer *n*, has been written carefully so that it works properly if *n = 0* or if *(−n)* would cause overflow.
It does not apply **mod** or **div** to negative arguments, since such operations are not implemented consistently by all Pascal compilers.

```c io/basic_printing.c
// prints an integer in decimal form
void print_int(int n) {
    int k = 0; // index to current digit; we assume that |n| < 10^{23}
    int m;     // used to negate |n| in possibly dangerous cases
    if (n < 0) {
        print_char('-');
        if (n > -100000000) {
            negate(n);
        }
        else {
            m = -1 - n;
            n = m / 10;
            m = (m % 10) + 1;
            k = 1;
            if (m < 10) {
                dig[0] = m;
            }
            else {
                dig[0] = 0;
                incr(n);
            }
        }
    }
    do {
        dig[k] = n % 10;
        n /= 10;
        incr(k);
    } while (n != 0);
    print_the_digs(k);
}
```
