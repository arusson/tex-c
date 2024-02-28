# Section 457

```c << Adjust for the magnification ratio >>=
prepare_mag();
if (mag != 1000) {
    cur_val = xn_over_d(cur_val, 1000, mag);
    f = (1000*f + 0x10000 * remainder_) / mag;
    cur_val += f / 0x10000;
    f %= 0x10000;
}
```
