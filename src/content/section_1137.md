# Section 1137

We get into math mode from horizontal mode when a '`$`' (i.e., a *MATH_SHIFT* character) is scanned.
We must check to see whether this '`$`' is immediately followed by another, in case display math mode is called for.

```c << Cases of |main_control| that build boxes and lists >>+=
case HMODE + MATH_SHIFT:
    init_math();
    break;
```
