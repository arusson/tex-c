# Section 820

```c << Initialize the special list heads and constant nodes >>+=
type(LAST_ACTIVE) = HYPHENATED;
line_number(LAST_ACTIVE) = MAX_HALFWORD;
subtype(LAST_ACTIVE) = 0; // the |subtype| is never examined by the algorithm
```
