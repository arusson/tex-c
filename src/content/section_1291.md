# Section 1291

```c include/constants.h
#define SHOW_CODE       0 // \show 
#define SHOW_BOX_CODE   1 // \showbox 
#define SHOW_THE_CODE   2 // \showthe 
#define SHOW_LISTS_CODE 3 // \showlists 
```

```c << Put each of TeX's primitives into the hash table >>+=
primitive("show", XRAY, SHOW_CODE);
primitive("showbox", XRAY, SHOW_BOX_CODE);
primitive("showthe", XRAY, SHOW_THE_CODE);
primitive("showlists", XRAY, SHOW_LISTS_CODE);
```
