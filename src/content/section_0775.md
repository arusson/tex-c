# Section 775

In vertical modes, *prev_depth* already has the correct value.
But if we are in *MMODE* (displayed formula mode), we reach out to the enclosing vertical mode for the *prev_depth* value that produces the correct baseline calculations.

```c << Change current mode to |-VMODE| for \halign, |-HMODE| for \valign >>=
if (mode == MMODE) {
    mode = -VMODE;
    prev_depth = nest[nest_ptr - 2].aux_field.sc;
}
else if (mode > 0) {
    negate(mode);
}
```
