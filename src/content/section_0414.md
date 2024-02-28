# Section 414

```c << Fetch a character code from some table >>=
scan_char_num();
if (m == MATH_CODE_BASE) {
    scanned_result(ho(math_code(cur_val)), INT_VAL);
}
else if (m < MATH_CODE_BASE) {
    scanned_result(equiv(m + cur_val), INT_VAL);
}
else {
    scanned_result(eqtb[m + cur_val].integer, INT_VAL);
}
```
