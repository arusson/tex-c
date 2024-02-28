# Section 1033

The boolean variables of the main loop are normally false, and always reset to false before the loop is left.
That saves us the extra work of initializing each time.

```c << Set initial values of key variables >>+=
ligature_present = false;
cancel_boundary = false;
lft_hit = false;
rt_hit = false;
ins_disc = false;
```
