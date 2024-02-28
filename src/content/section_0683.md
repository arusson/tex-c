# Section 683

A *RADICAL_NOAD* is five words long; the fifth word is the *left_delimiter* field, which usually represents a square root sign.

A *FRACTION_NOAD* is six words long; it has a *right_delimiter* field as well as a *left_delimiter*.

Delimiter fields are of type *four_quarters*, and they have four subfields called *small_fam*, *small_char*, *large_fam*, *large_char*.
These subfields represent variable-size delimiters by giving the "small" and "large" starting characters, as explained in Chapter&nbsp;17 of *The TeXbook*.

A *FRACTION_NOAD* is actually quite different from all other noads.
Not only does it have six words, it has *thickness*, *denominator*, and *numerator* fields instead of *nucleus*, *subscr*, and *supscr*.
The *thickness* is a scaled value that tells how thick to make a fraction rule; however, the special value *DEFAULT_CODE* is used to stand for the *default_rule_thickness* of the current size.
The *numerator* and *denominator* point to mlists that define a fraction; we always have

<div align="center">

*math_type(numerator) = math_type(denominator) = SUB_MLIST*.
</div>

The *left_delimiter* and *right_delimiter* fields specify delimiters that will be placed at the left and right of the fraction.
In this way, a *FRACTION_NOAD* is able to represent all of $\TeX$'s operators `\over`, `\atop`, `\above`, `\overwithdelims`, `\atopwithdelims`, and `\abovewithdelims`.

```c include/constants.h
#define RADICAL_NOAD       (INNER_NOAD + 1)   // |type| of a noad for square roots
#define RADICAL_NOAD_SIZE  5                  // number of |mem| words in a radical noad
#define FRACTION_NOAD      (RADICAL_NOAD + 1) // |type| of a noad for generalized fractions
#define FRACTION_NOAD_SIZE 6                  // number of |mem| words in a fraction noad
#define DEFAULT_CODE       0x40000000         // denotes |default_rule_thickness|
```

```c include/texmath.h
#define left_delimiter(X)  ((X) + 4)         // first delimiter field of a noad
#define right_delimiter(X) ((X) + 5)         // second delimiter field of a fraction noad
#define small_fam(X)       qqqq_b0(mem[(X)]) // |fam| for "small" delimiter
#define small_char(X)      qqqq_b1(mem[(X)]) // |character| for "small" delimiter
#define large_fam(X)       qqqq_b2(mem[(X)]) // |fam| for "large" delimiter
#define large_char(X)      qqqq_b3(mem[(X)]) // |character| for "large" delimiter
#define thickness          width             // |thickness| field in a fraction noad
#define numerator          supscr            // |numerator| field in a fraction noad
#define denominator        subscr            // |denominator| field in a fraction noad
```
