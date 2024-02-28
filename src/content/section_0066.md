# Section 66

Here is a trivial procedure to print two digits; it is usually called with a parameter in the range *0* $\leq$ *n* $\leq$ *99*.

```c io/basic_printing.c
// prints two least significant digits
void print_two(int n) {
    n = abs(n) % 100;
    print_char('0' + (n / 10));
    print_char('0' + (n % 10));
}
```
