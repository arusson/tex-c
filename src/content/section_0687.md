# Section 687

A few more kinds of noads will complete the set: An *UNDER_NOAD* has its nucleus underlined; an *OVER_NOAD* has it overlined.
An *ACCENT_NOAD* places an accent over its nucleus; the accent character appears as *fam(accent_chr(p))* and *character(accent_chr(p))*.
A *VCENTER_NOAD* centers its nucleus vertically with respect to the axis of the formula;
in such noads we always have *math_type(nucleus(p)) = sub_box*.

And finally, we have *LEFT_NOAD* and *RIGHT_NOAD* types, to implement $\TeX$'s `\left` and `\right`.
The *nucleus* of such noads is replaced by a *delimiter* field; thus, for example, '`\left(`' produces a *LEFT_NOAD* such that *delimiter(p)* holds the family and character codes for all left parentheses.
A *LEFT_NOAD* never appears in an mlist except as the first element, and a *RIGHT_NOAD* never appears in an mlist except as the last element;
furthermore, we either have both a *LEFT_NOAD* and a *RIGHT_NOAD*, or neither one is present.
The *subscr* and *supscr* fields are always *empty* in a *LEFT_NOAD* and a *RIGHT_NOAD*.

```c include/constants.h
#define UNDER_NOAD       (FRACTION_NOAD + 1) // |type| of a noad for underlining
#define OVER_NOAD        (UNDER_NOAD + 1)    // |type| of a noad for overlining
#define ACCENT_NOAD      (OVER_NOAD + 1)     // |type| of a noad for accented subformulas
#define ACCENT_NOAD_SIZE 5                   // number of |mem| words in an accent noad
#define VCENTER_NOAD     (ACCENT_NOAD + 1)   // |type| of a noad for \vcenter
#define LEFT_NOAD        (VCENTER_NOAD + 1)  // |type| of a noad for \left
#define RIGHT_NOAD       (LEFT_NOAD + 1)     // |type| of a noad for \right
```

```c include/texmath.h
#define accent_chr(X)      ((X) + 4) // the |accent_chr| field of an accent noad
#define delimiter          nucleus   // |delimiter| field in left and right noads
#define scripts_allowed(X) (type((X)) >= ORD_NOAD && type((X)) < LEFT_NOAD)
```
