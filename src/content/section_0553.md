# Section 553

> ![NOTE]
> String "`nullfont`" is added a second time to the pool.
> Too bad.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("nullfont", SET_FONT, NULL_FONT);
text(FROZEN_NULL_FONT) = str_ptr - 1;
eqtb[FROZEN_NULL_FONT] = eqtb[cur_val];
```
