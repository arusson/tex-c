# Section 1156

Primitive math operators like `\mathop` and `\underline` are given the command code *MATH_COMP*, supplemented by the noad type that they generate.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("mathord", MATH_COMP, ORD_NOAD);
primitive("mathop", MATH_COMP, OP_NOAD);
primitive("mathbin", MATH_COMP, BIN_NOAD);
primitive("mathrel", MATH_COMP, REL_NOAD);
primitive("mathopen", MATH_COMP, OPEN_NOAD);
primitive("mathclose", MATH_COMP, CLOSE_NOAD);
primitive("mathpunct", MATH_COMP, PUNCT_NOAD);
primitive("mathinner", MATH_COMP, INNER_NOAD);
primitive("underline", MATH_COMP, UNDER_NOAD);
primitive("overline", MATH_COMP, OVER_NOAD);
primitive("displaylimits", LIMIT_SWITCH, NORMAL);
primitive("limits", LIMIT_SWITCH, LIMITS);
primitive("nolimits", LIMIT_SWITCH, NO_LIMITS);
```
