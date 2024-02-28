# Section 487: Conditional processing

We consider now the way $\TeX$ handles various kinds of `\if` commands.

```c include/constants.h
#define IF_CHAR_CODE  0   // '\if' 
#define IF_CAT_CODE   1   // '\ifcat' 
#define IF_INT_CODE   2   // '\ifnum' 
#define IF_DIM_CODE   3   // '\ifdim' 
#define IF_ODD_CODE   4   // '\ifodd' 
#define IF_VMODE_CODE 5   // '\ifvmode' 
#define IF_HMODE_CODE 6   // '\ifhmode' 
#define IF_MMODE_CODE 7   // '\ifmmode' 
#define IF_INNER_CODE 8   // '\ifinner' 
#define IF_VOID_CODE  9   // '\ifvoid' 
#define IF_HBOX_CODE  10  // '\ifhbox' 
#define IF_VBOX_CODE  11  // '\ifvbox' 
#define IFX_CODE      12  // '\ifx' 
#define IF_EOF_CODE   13  // '\ifeof' 
#define IF_TRUE_CODE  14  // '\iftrue' 
#define IF_FALSE_CODE 15  // '\iffalse' 
#define IF_CASE_CODE  16  // '\ifcase' 
```

```c << Put each of TeX's primitives into the hash table >>+=
primitive("if", IF_TEST, IF_CHAR_CODE);
primitive("ifcat", IF_TEST, IF_CAT_CODE);
primitive("ifnum", IF_TEST, IF_INT_CODE);
primitive("ifdim", IF_TEST, IF_DIM_CODE);
primitive("ifodd", IF_TEST, IF_ODD_CODE);
primitive("ifvmode", IF_TEST, IF_VMODE_CODE);
primitive("ifhmode", IF_TEST, IF_HMODE_CODE);
primitive("ifmmode", IF_TEST, IF_MMODE_CODE);
primitive("ifinner", IF_TEST, IF_INNER_CODE);
primitive("ifvoid", IF_TEST, IF_VOID_CODE);
primitive("ifhbox", IF_TEST, IF_HBOX_CODE);
primitive("ifvbox", IF_TEST, IF_VBOX_CODE);
primitive("ifx", IF_TEST, IFX_CODE);
primitive("ifeof", IF_TEST, IF_EOF_CODE);
primitive("iftrue", IF_TEST, IF_TRUE_CODE);
primitive("iffalse", IF_TEST, IF_FALSE_CODE);
primitive("ifcase", IF_TEST, IF_CASE_CODE);
```
