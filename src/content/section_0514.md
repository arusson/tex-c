# Section 514

Input files that can't be found in the user's area may appear in a standard system area called *TEX_AREA*.
Font metric files whose areas are not given explicitly are assumed to appear in a standard system area called *TEX_FONT_AREA*.
These system area names will, of course, vary from place to place.

> ![NOTE]
> Those strings are added to the pool (with '`/`' as separator instead of '`:`').

```c << Read the other strings >>+=
put_string("TeXinputs/"); // TEX_AREA: 258
put_string("TeXfonts/");  // TEX_FONT_AREA: 259
```

```c << Internal strings numbers in the pool >>+=
#define TEX_AREA 258
#define TEX_FONT_AREA 259
```
