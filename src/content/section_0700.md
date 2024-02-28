# Section 700

Before an mlist is converted to an hlist, $\TeX$ makes sure that the fonts in family&nbsp;2 have enough parameters to be math-symbol fonts, and that the fonts in family&nbsp;3 have enough parameters to be math-extension fonts.
The math-symbol parameters are referred to by using the following macros, which take a size code as their parameter; for example, *num1(cur_size)* gives the value of the *num1* parameter for the current size.

```c include/constants.h
#define TOTAL_MATHSY_PARAMS 22
```

```c include/texmath.h
#define mathsy(X, Y)     font_info[(X) + param_base[fam_fnt(2 + (Y))]].sc
#define math_x_height(X) mathsy(5, (X))  // height of 'x'
#define math_quad(X)     mathsy(6, (X))  // 18mu
#define num1(X)          mathsy(8, (X))  // numerator shift-up in display styles
#define num2(X)          mathsy(9, (X))  // numerator shift-up in non - display, non-\atop
#define num3(X)          mathsy(10, (X)) // numerator shift-up in non-display \atop
#define denom1(X)        mathsy(11, (X)) // denominator shift-down in display styles
#define denom2(X)        mathsy(12, (X)) // denominator shift-down in non-display styles
#define sup1(X)          mathsy(13, (X)) // superscript shift-up in uncramped display style
#define sup2(X)          mathsy(14, (X)) // superscript shift-up in uncramped non-display
#define sup3(X)          mathsy(15, (X)) // superscript shift-up in cramped styles
#define sub1(X)          mathsy(16, (X)) // subscript shift-down if superscript is absent
#define sub2(X)          mathsy(17, (X)) // subscript shift-down if superscript is present
#define sup_drop(X)      mathsy(18, (X)) // superscript baseline below top of large box
#define sub_drop(X)      mathsy(19, (X)) // subscript baseline below bottom of large box
#define delim1(X)        mathsy(20, (X)) // size of \atopwithdelims delimiters in display styles
#define delim2(X)        mathsy(21, (X)) // size of \atopwithdelims delimiters in non - displays
#define axis_height(X)   mathsy(22, (X)) // height of fraction lines above the baseline
```
