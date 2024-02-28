# Section 221

Each entry in *eqtb* is a *memory_word*. Most of these words are of type
*two_halves*, and subdivided into three fields:

1. The *eq_level* (a quarterword) is the level of grouping at
   which this equivalent was defined. If the level is *LEVEL_ZERO*, the
   equivalent has never been defined; *LEVEL_ONE* refers to the outer level
   (outside of all groups), and this level is also used for global
   definitions that never go away. Higher levels are for equivalents that
   will disappear at the end of their group.

2. The *eq_type* (another quarterword) specifies what kind of
   entry this is. There are many types, since each $\TeX$ primitive like
   `\hbox`, `\def`, etc., has its own special code. The list of
   command codes above includes all possible settings of the *eq_type* field.

3. The *equiv* (a halfword) is the current equivalent value.
   This may be a font number, a pointer into *mem*, or a variety of other things.

```c include/constants.h
#define LEVEL_ZERO MIN_QUARTERWORD // level for undefined quantities
#define LEVEL_ONE (LEVEL_ZERO + 1) // outermost level for defined quantities
```

```c include/datastructures.h
#define eq_level_field(X) hh_b1((X))
#define eq_type_field(X)  hh_b0((X))
#define equiv_field(X)    hh_rh((X))

#define eq_level(X) eq_level_field(eqtb[(X)]) // level of definition
#define eq_type(X)  eq_type_field(eqtb[(X)])  // command code for equivalent
#define equiv(X)    equiv_field(eqtb[(X)])    // equivalent value
```
