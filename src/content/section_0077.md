# Section 77

The value of *history* is initially *FATAL_ERROR_STOP*, but it will be changed to *SPOTLESS* if $\TeX$ survives the initialization process.

```c << Set initial values of key variables >>+=
deletions_allowed = true;
set_box_allowed = true;
error_count = 0;
// history is initialized elsewhere
```
