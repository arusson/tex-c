# Section 1058

The *HSKIP* and *VSKIP* command codes are used for control sequences like `\hss` and `\vfil` as well as for `\hskip` and `\vskip`.
The difference is in the value of *cur_chr*.

```c include/constants.h
#define FIL_CODE     0 // identifies \hfil and \vfil
#define FILL_CODE    1 // identifies \hfill and \vfill
#define SS_CODE      2 // identifies \hss and \vss
#define FIL_NEG_CODE 3 // identifies \hfilneg and \vfilneg
#define SKIP_CODE    4 // identifies \hskip and \vskip
#define MSKIP_CODE   5 // identifies \mskip
```

```c << Put each of TeX's primitives into the hash table >>+=
primitive("hskip", HSKIP, SKIP_CODE);
primitive("hfil", HSKIP, FIL_CODE);
primitive("hfill", HSKIP, FILL_CODE);
primitive("hss", HSKIP, SS_CODE);
primitive("hfilneg", HSKIP, FIL_NEG_CODE);
primitive("vskip", VSKIP, SKIP_CODE);
primitive("vfil", VSKIP, FIL_CODE);
primitive("vfill", VSKIP, FILL_CODE);
primitive("vss", VSKIP, SS_CODE);
primitive("vfilneg", VSKIP, FIL_NEG_CODE);
primitive("mskip", MSKIP, MSKIP_CODE);
primitive("kern", KERN, EXPLICIT);
primitive("mkern", MKERN, MU_GLUE);
```
