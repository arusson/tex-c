# Section 1046

Here is a list of cases where the user has probably gotten into or out of math mode by mistake.
$\TeX$ will insert a dollar sign and rescan the current token.

```c include/builder.h
#define non_math(X)   \
    case VMODE + (X): \
    case HMODE + (X)
```

```c << Math-only cases in non-math modes, or vice versa >>=
non_math(SUP_MARK):
non_math(SUB_MARK):
non_math(MATH_CHAR_NUM):
non_math(MATH_GIVEN):
non_math(MATH_COMP):
non_math(DELIM_NUM):
non_math(LEFT_RIGHT):
non_math(ABOVE):
non_math(RADICAL):
non_math(MATH_STYLE):
non_math(MATH_CHOICE):
non_math(VCENTER):
non_math(NON_SCRIPT):
non_math(MKERN):
non_math(LIMIT_SWITCH):
non_math(MSKIP):
non_math(MATH_ACCENT):
case MMODE + ENDV:
case MMODE + PAR_END:
case MMODE + STOP:
case MMODE + VSKIP:
case MMODE + UN_VBOX:
case MMODE + VALIGN:
case MMODE + HRULE:
```
