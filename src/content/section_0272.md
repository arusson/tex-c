# Section 272

At this time it might be a good idea for the reader to review the introduction to *eqtb* that was given above just before the long lists of parameter names.
Recall that the "outer level" of the program is *LEVEL_ONE*, since undefined control sequences are assumed to be "defined" at *LEVEL_ZERO*.

```c << Set initial values of key variables >>+=
save_ptr = 0;
cur_level = LEVEL_ONE;
cur_group = BOTTOM_LEVEL;
cur_boundary = 0;
max_save_stack = 0;
```
