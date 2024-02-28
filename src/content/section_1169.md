# Section 1169

The routine that inserts a *STYLE_NODE* holds no surprises.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("displaystyle", MATH_STYLE, DISPLAY_STYLE);
primitive("textstyle", MATH_STYLE, TEXT_STYLE);
primitive("scriptstyle", MATH_STYLE, SCRIPT_STYLE);
primitive("scriptscriptstyle", MATH_STYLE, SCRIPT_SCRIPT_STYLE);
```
