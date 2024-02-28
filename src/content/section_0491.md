# Section 491

```c << Put each of TeX's primitives into the hash table >>+=
primitive("fi", FI_OR_ELSE, FI_CODE);
text(FROZEN_FI) = str_ptr - 1; // "fi"
eqtb[FROZEN_FI] = eqtb[cur_val];
primitive("or", FI_OR_ELSE, OR_CODE);
primitive("else", FI_OR_ELSE, ELSE_CODE);
```
