# Section 416

Users refer to '`\the\spacefactor`' only in horizontal mode, and to '`\the\prevdepth`' only in vertical mode; so we put the associated mode in the modifier part of the *SET_AUX* command.
The *SET_PAGE_INT* command has modifier 0 or 1, for '`\deadcycles`' and '`\insertpenalties`', respectively.
The *SET_BOX_DIMEN* command is modified by either *WIDTH_OFFSET*, *HEIGHT_OFFSET*, or *DEPTH_OFFSET*.
And the *LAST_ITEM* command is modified by either *INT_VAL*, *DIMEN_VAL*,
*GLUE_VAL*, *INPUT_LINE_NO_CODE*, or *BADNESS_CODE*.

```c include/constants.h
#define INPUT_LINE_NO_CODE (GLUE_VAL + 1) // code for \inputlineno
#define BADNESS_CODE       (GLUE_VAL + 2) // code for \badness
```

```c << Put each of TeX's primitives into the hash table >>+=
primitive("spacefactor", SET_AUX, HMODE);
primitive("prevdepth", SET_AUX, VMODE);
primitive("deadcycles", SET_PAGE_INT, 0);
primitive("insertpenalties", SET_PAGE_INT, 1);
primitive("wd", SET_BOX_DIMEN, WIDTH_OFFSET);
primitive("ht", SET_BOX_DIMEN, HEIGHT_OFFSET);
primitive("dp", SET_BOX_DIMEN, DEPTH_OFFSET);
primitive("lastpenalty", LAST_ITEM, INT_VAL);
primitive("lastkern", LAST_ITEM, DIMEN_VAL);
primitive("lastskip", LAST_ITEM, GLUE_VAL);
primitive("inputlineno", LAST_ITEM, INPUT_LINE_NO_CODE);
primitive("badness", LAST_ITEM, BADNESS_CODE);
```
