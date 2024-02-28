# Section 427

```c << Fetch a register >>=
scan_eight_bit_int();
switch (m) {
case INT_VAL:
    cur_val = count(cur_val);
    break;

case DIMEN_VAL:
    cur_val = dimen(cur_val);
    break;

case GLUE_VAL:
    cur_val = skip(cur_val);
    break;

case MU_VAL:
    cur_val = mu_skip(cur_val);
} // there are no other cases
cur_val_level = m;
```
