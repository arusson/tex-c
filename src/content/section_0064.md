# Section 64

An array of digits in the range *0 .. 15* is printed by *print_the_digs*.

```c io/basic_printing.c
// prints |dig[k - 1]| ... |dig[0]|
void print_the_digs(eight_bits k) {
    while (k > 0) {
        decr(k);
        if (dig[k] < 10) {
            print_char('0' + dig[k]);
        }
        else {
            print_char('A' - 10 + dig[k]);
        }
    }
}
```
