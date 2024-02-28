# Section 410

TeX doesn't know exactly what to expect when *scan_something_internal* begins.
For example, an integer or dimension or glue value could occur immediately after '`\hskip`'; and one can even say `\the` with respect to token lists in constructions like
'`\xdef\o{\the\output}`'.
On the other hand, only integers are allowed after a construction like '`\count`'.
To handle the various possibilities, *scan_something_internal* has a *level* parameter, which tells the "highest" kind of quantity that *scan_something_internal* is allowed to produce.
Six levels are distinguished, namely *INT_VAL*, *DIMEN_VAL*, *GLUE_VAL*, *MU_VAL*, *IDENT_VAL*, and *TOK_VAL*.

The output of *scan_something_internal* (and of the other routines *scan_int*, *scan_dimen*, and *scan_glue* below) is put into the global variable *cur_val*, and its level is put into *cur_val_level*.
The highest values of *cur_val_level* are special: *MU_VAL* is used only when *cur_val* points to something in a "muskip" register, or to one of the three parameters `\thinmuskip`, `\medmuskip`, `\thickmuskip`;
*IDENT_VAL* is used only when *cur_val* points to a font identifier;
*TOK_VAL* is used only when *cur_val* points to *null* or to the reference count of a token list.
The last two cases are allowed only when *scan_something_internal* is called with *level = TOK_VAL*.

If the output is glue, *cur_val* will point to a glue specification, and the reference count of that glue will have been updated to reflect this reference; if the output is a nonempty token list, *cur_val* will point to its reference count, but in this case the count will not have been updated.
Otherwise *cur_val* will contain the integer or scaled value in question.

```c include/constants.h
#define INT_VAL   0 // integer values
#define DIMEN_VAL 1 // dimension values
#define GLUE_VAL  2 // glue specifications
#define MU_VAL    3 // math glue specifications
#define IDENT_VAL 4 // font identifier
#define TOK_VAL   5 // token lists
```

```c << Global variables >>+=
int cur_val;       // value returned by numeric scanners
int cur_val_level; // the "level" of this value
```
