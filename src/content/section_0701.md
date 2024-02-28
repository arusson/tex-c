# Section 701

The math-extension parameters have similar macros, but the size code is omitted (since it is always *cur_size* when we refer to such parameters).

```c include/constants.h
#define TOTAL_MATHEX_PARAMS 13
```

```c include/texmath.h
#define mathex(X)              font_info[(X) + param_base[fam_fnt(3 + cur_size)]].sc
#define default_rule_thickness mathex(8)  // thickness of \\over} bars
#define big_op_spacing1        mathex(9)  // minimum clearance above a displayed op
#define big_op_spacing2        mathex(10) // minimum clearance below a displayed op
#define big_op_spacing3        mathex(11) // minimum baselineskip above displayed op
#define big_op_spacing4        mathex(12) // minimum baselineskip below displayed op
#define big_op_spacing5        mathex(13) // padding above and below displayed limits
```
