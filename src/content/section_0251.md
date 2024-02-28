# Section 251

```c << Show equivalent |n|, in region 6 >>=
if (n < SCALED_BASE) {
    print_length_param(n - DIMEN_BASE);
}
else {
    print_esc("dimen");
    print_int(n - SCALED_BASE);
}
print_char('=');
print_scaled(eqtb[n].sc);
print("pt");
```
