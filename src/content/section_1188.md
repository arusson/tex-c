# Section 1188

We have dealt with all constructions of math mode except '`\left`' and '`\right`', so the picture is completed by the following sections of the program.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("left", LEFT_RIGHT, LEFT_NOAD);
primitive("right", LEFT_RIGHT, RIGHT_NOAD);
text(FROZEN_RIGHT) = str_ptr - 1; // "right"
eqtb[FROZEN_RIGHT] = eqtb[cur_val];
```
