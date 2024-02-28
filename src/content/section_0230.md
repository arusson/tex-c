# Section 230

Region 4 of *eqtb* contains the local quantities defined here.
The bulk of this region is taken up by five tables that are indexed by eight-bit characters;
these tables are important to both the syntactic and semantic portions of $\TeX$.
There are also a bunch of special things like font and token parameters, as well as the tables of `\toks` and `\box` registers.

```c include/constants.h
#define PAR_SHAPE_LOC      LOCAL_BASE             // specifies paragraph shape
#define OUTPUT_ROUTINE_LOC (LOCAL_BASE + 1)       // points to token list for \output
#define EVERY_PAR_LOC      (LOCAL_BASE + 2)       // points to token list for \everypar
#define EVERY_MATH_LOC     (LOCAL_BASE + 3)       // points to token list for \everymath
#define EVERY_DISPLAY_LOC  (LOCAL_BASE + 4)       // points to token list for \everydisplay
#define EVERY_HBOX_LOC     (LOCAL_BASE + 5)       // points to token list for \everyhbox
#define EVERY_VBOX_LOC     (LOCAL_BASE + 6)       // points to token list for \everyvbox
#define EVERY_JOB_LOC      (LOCAL_BASE + 7)       // points to token list for \everyjob
#define EVERY_CR_LOC       (LOCAL_BASE + 8)       // points to token list for \everycr
#define ERR_HELP_LOC       (LOCAL_BASE + 9)       // points to token list for \errhelp
#define TOKS_BASE          (LOCAL_BASE + 10)      // table of 256 token list registers
#define BOX_BASE           (TOKS_BASE + 256)      // table of 256 box registers
#define CUR_FONT_LOC       (BOX_BASE + 256)       // internal font number outside math mode
#define MATH_FONT_BASE     (CUR_FONT_LOC + 1)     // table of 48 math font numbers
#define CAT_CODE_BASE      (MATH_FONT_BASE + 48)  // table of 256 command codes (the "catcodes")
#define LC_CODE_BASE       (CAT_CODE_BASE + 256)  // table of 256 lowercase mappings
#define UC_CODE_BASE       (LC_CODE_BASE + 256)   // table of 256 uppercase mappings
#define SF_CODE_BASE       (UC_CODE_BASE + 256)   // table of 256 spacefactor mappings
#define MATH_CODE_BASE     (SF_CODE_BASE + 256)   // table of 256 math mode mappings
#define INT_BASE           (MATH_CODE_BASE + 256) // beginning of region 5
```

```c include/datastructures.h
#define par_shape_ptr  equiv(PAR_SHAPE_LOC)
#define output_routine equiv(OUTPUT_ROUTINE_LOC)
#define every_par      equiv(EVERY_PAR_LOC)
#define every_math     equiv(EVERY_MATH_LOC)
#define every_display  equiv(EVERY_DISPLAY_LOC)
#define every_hbox     equiv(EVERY_HBOX_LOC)
#define every_vbox     equiv(EVERY_VBOX_LOC)
#define every_job      equiv(EVERY_JOB_LOC)
#define every_cr       equiv(EVERY_CR_LOC)
#define err_help       equiv(ERR_HELP_LOC)
#define toks(X)        equiv(TOKS_BASE + (X))
#define box(X)         equiv(BOX_BASE + (X))
#define cur_font       equiv(CUR_FONT_LOC)
#define fam_fnt(X)     equiv(MATH_FONT_BASE + (X))
#define cat_code(X)    equiv(CAT_CODE_BASE + (X))
#define lc_code(X)     equiv(LC_CODE_BASE + (X))
#define uc_code(X)     equiv(UC_CODE_BASE + (X))
#define sf_code(X)     equiv(SF_CODE_BASE + (X))
// Note: |math_code(c)| is the true math code plus |MIN_HALFWORD|
#define math_code(X)   equiv(MATH_CODE_BASE + (X))
```

```c << Put each of TeX's primitives into the hash table >>+=
primitive("output", ASSIGN_TOKS, OUTPUT_ROUTINE_LOC);
primitive("everypar", ASSIGN_TOKS, EVERY_PAR_LOC);
primitive("everymath", ASSIGN_TOKS, EVERY_MATH_LOC);
primitive("everydisplay", ASSIGN_TOKS, EVERY_DISPLAY_LOC);
primitive("everyhbox", ASSIGN_TOKS, EVERY_HBOX_LOC);
primitive("everyvbox", ASSIGN_TOKS, EVERY_VBOX_LOC);
primitive("everyjob", ASSIGN_TOKS, EVERY_JOB_LOC);
primitive("everycr", ASSIGN_TOKS, EVERY_CR_LOC);
primitive("errhelp", ASSIGN_TOKS, ERR_HELP_LOC);
```
