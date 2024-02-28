# Section 209

The next codes are special; they all relate to mode-independent assignment of values to $\TeX$'s internal registers or tables.
Codes that are *MAX_INTERNAL* or less represent internal quantities that might be expanded by '`\the`'.

```c include/constants.h
#define TOKS_REGISTER     71  // token list register (\toks)
#define ASSIGN_TOKS       72  // special token list (\output, \everypar, etc.)
#define ASSIGN_INT        73  // user-defined integer (\tolerance, \day, etc.)
#define ASSIGN_DIMEN      74  // user-defined length (\hsize, etc.)
#define ASSIGN_GLUE       75  // user-defined glue (\baselineskip, etc.)
#define ASSIGN_MU_GLUE    76  // user-defined muglue (\thinmuskip, etc.)
#define ASSIGN_FONT_DIMEN 77  // user-defined font dimension (\fontdimen)
#define ASSIGN_FONT_INT   78  // user-defined font integer (\hyphenchar, \skewchar)
#define SET_AUX           79  // specify state info (\spacefactor, \prevdepth)
#define SET_PREV_GRAF     80  // specify state info (\prevgraf)
#define SET_PAGE_DIMEN    81  // specify state info (\pagegoal, etc.)
#define SET_PAGE_INT      82  // specify state info (\deadcycles, \insertpenalties)
#define SET_BOX_DIMEN     83  // change dimension of box (\wd, \ht, \dp)
#define SET_SHAPE         84  // specify fancy paragraph shape (\parshape)
#define DEF_CODE          85  // define a character code (\catcode, etc.)
#define DEF_FAMILY        86  // declare math fonts (\textfont, etc.)
#define SET_FONT          87  // set current font (font identifiers)
#define DEF_FONT          88  // define a font file (\font)
#define REGISTER          89  // internal register (\count, \dimen, etc.)
#define MAX_INTERNAL      89  // the largest code that can follow \the
#define ADVANCE           90  // advance a register or parameter (\advance)
#define MULTIPLY          91  // multiply a register or parameter (\multiply)
#define DIVIDE            92  // divide a register or parameter (\divide)
#define PREFIX            93  // qualify a definition (\global, \long, \outer)
#define LET               94  // assign a command code (\let, \futurelet)
#define SHORTHAND_DEF     95  // code definition (\chardef, \countdef, etc.)
#define READ_TO_CS        96  // read into a control sequence (\read)
#define DEF               97  // macro definition (\def, \gdef, \xdef, \edef)
#define SET_BOX           98  // set a box (\setbox)
#define HYPH_DATA         99  // hyphenation data (\hyphenation, \patterns)
#define SET_INTERACTION   100 // define level of interaction (\batchmode, etc.)
#define MAX_COMMAND       100 // the largest command code seen at |big_switch|
```
