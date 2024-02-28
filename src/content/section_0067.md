# Section 67

Hexadecimal printing of nonnegative integers is accomplished by *print_hex*.

```c io/basic_printing.c
// prints a positive integer in hexadecimal form
void print_hex(int n) {
    int k = 0; // index to current digit; we assume that 0 <= n < 16^{22}
    print_char('"');
    do {
        dig[k] = n % 16;
        n /= 16;
        incr(k);
    } while (n != 0);
    print_the_digs(k);
}
```
