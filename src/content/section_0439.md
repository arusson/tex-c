# Section 439

We initialize the following global variables just in case *expand* comes into action before any of the basic scanning routines has assigned them a value.

```c << Set initial values of key variables >>+=
cur_val = 0;
cur_val_level = INT_VAL;
radix = 0;
cur_order = NORMAL;
```
