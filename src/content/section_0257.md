# Section 257

```c << Set initial values of key variables >>+=
no_new_control_sequence = true; // new identifiers are usually forbidden
next(HASH_BASE) = 0;
text(HASH_BASE) = 0;
for(k = HASH_BASE + 1;  k < UNDEFINED_CONTROL_SEQUENCE; k++) {
    hash[k] = hash[HASH_BASE];
}
```
