# Section 1230

The various character code tables are changed by the *DEF_CODE* commands, and the font families are declared by *DEF_FAMILY*.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("catcode", DEF_CODE, CAT_CODE_BASE);
primitive("mathcode", DEF_CODE, MATH_CODE_BASE);
primitive("lccode", DEF_CODE, LC_CODE_BASE);
primitive("uccode", DEF_CODE, UC_CODE_BASE);
primitive("sfcode", DEF_CODE, SF_CODE_BASE);
primitive("delcode", DEF_CODE, DEL_CODE_BASE);
primitive("textfont", DEF_FAMILY, MATH_FONT_BASE);
primitive("scriptfont", DEF_FAMILY, MATH_FONT_BASE + SCRIPT_SIZE);
primitive("scriptscriptfont", DEF_FAMILY, MATH_FONT_BASE + SCRIPT_SCRIPT_SIZE);
```
