# Section 1259

```c << Put the (positive) 'at' size into |s| >>=
scan_normal_dimen;
s = cur_val;
if (s <= 0 || s >= 0x8000000) {
    print_err("Improper `at' size (");
    print_scaled(s);
    print("pt), replaced by 10pt");
    help2("I can only handle fonts at positive sizes that are")
        ("less than 2048pt, so I've changed what you said to 10pt.");
    error();
    s = 10*UNITY;
}
```
