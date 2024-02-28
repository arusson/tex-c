# Section 1182

```c << Use code |c| to distinguish between generalized fractions >>=
if (c >= DELIMITED_CODE) {
    scan_delimiter(left_delimiter(incompleat_noad), false);
    scan_delimiter(right_delimiter(incompleat_noad), false);
}
switch (c % DELIMITED_CODE) {
case ABOVE_CODE:
    scan_normal_dimen;
    thickness(incompleat_noad) = cur_val;
    break;

case OVER_CODE:
    thickness(incompleat_noad) = DEFAULT_CODE;
    break;

case ATOP_CODE:
    thickness(incompleat_noad) = 0;
} // there are no other cases
```
