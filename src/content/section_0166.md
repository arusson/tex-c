# Section 166

```c << Set initial values of key variables >>+=
#ifdef DEBUG
was_mem_end = MEM_MIN; // indicate that everything was previously free
was_lo_max = MEM_MIN;
was_hi_min = MEM_MAX;
panicking = false;
#endif
```
