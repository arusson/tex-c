# Section 893

Hyphenation routines need a few more local variables.

```c << Local variables for line breaking >>+=
small_number j; // an index into |hc| or |hu|
unsigned char c; // character being considered for hyphenation
```
