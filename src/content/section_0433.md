# Section 433

```c << Declare procedures that scan restricted classes of integers >>=
void scan_eight_bit_int() {
    scan_int();
    if (cur_val < 0 || cur_val > 255) {
        print_err("Bad register code");        
        help2("A register number must be between 0 and 255.")
            ("I changed this one to zero.");
        int_error(cur_val);
        cur_val = 0;
    }
}
```
