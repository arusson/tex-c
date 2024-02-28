# Section 1344

Extensions might introduce new command codes; but it's best to use *EXTENSION* with a modifier, whenever possible, so that *main_control* stays the same.

```c include/constants.h
#define IMMEDIATE_CODE    4 // command modifier for \immediate
#define SET_LANGUAGE_CODE 5 // command modifier for \setlanguage
```

```c << Put each of TeX's primitives into the hash table >>+=
primitive("openout", EXTENSION, OPEN_NODE);
primitive("write", EXTENSION, WRITE_NODE);
write_loc = cur_val;
primitive("closeout", EXTENSION, CLOSE_NODE);
primitive("special", EXTENSION, SPECIAL_NODE);
primitive("immediate", EXTENSION, IMMEDIATE_CODE);
primitive("setlanguage", EXTENSION, SET_LANGUAGE_CODE);
```
