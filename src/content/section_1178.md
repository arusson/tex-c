# Section 1178

An operation like '`\over`' causes the current mlist to go into a state of suspended animation: *incompleat_noad* points to a *FRACTION_NOAD* that contains the mlist-so-far as its numerator, while the denominator is yet to come.
Finally when the mlist is finished, the denominator will go into the incompleat fraction noad, and that noad will become the whole formula, unless it is surrounded by '`\left`' and '`\right`' delimiters.

```c include/constants.h
#define ABOVE_CODE     0 // '\above' 
#define OVER_CODE      1 // '\over' 
#define ATOP_CODE      2 // '\atop' 
#define DELIMITED_CODE 3 // '\abovewithdelims', etc.
```

```c << Put each of TeX's primitives into the hash table >>+=
primitive("above", ABOVE, ABOVE_CODE);
primitive("over", ABOVE, OVER_CODE);
primitive("atop", ABOVE, ATOP_CODE);
primitive("abovewithdelims", ABOVE, DELIMITED_CODE + ABOVE_CODE);
primitive("overwithdelims", ABOVE, DELIMITED_CODE + OVER_CODE);
primitive("atopwithdelims", ABOVE, DELIMITED_CODE + ATOP_CODE);
```
