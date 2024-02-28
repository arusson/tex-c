# Section 1222

A `\chardef` creates a control sequence whose *cmd* is *CHAR_GIVEN*;
a `\mathchardef` creates a control sequence whose *cmd* is *MATH_GIVEN*;
and the corresponding *chr* is the character code or math code.
A `\countdef` or `\dimendef` or `\skipdef` or `\muskipdef` creates a control sequence whose *cmd* is *ASSIGN_INT* or $\ldots$ or *ASSIGN_MU_GLUE*, and the corresponding *chr* is the *eqtb* location of the internal register in question.

```c include/constants.h
#define CHAR_DEF_CODE      0 // |shorthand_def| for \chardef
#define MATH_CHAR_DEF_CODE 1 // |shorthand_def| for \mathchardef
#define COUNT_DEF_CODE     2 // |shorthand_def| for \countdef
#define DIMEN_DEF_CODE     3 // |shorthand_def| for \dimendef
#define SKIP_DEF_CODE      4 // |shorthand_def| for \skipdef
#define MU_SKIP_DEF_CODE   5 // |shorthand_def| for \muskipdef
#define TOKS_DEF_CODE      6 // |shorthand_def| for \toksdef
```

```c << Put each of TeX's primitives into the hash table >>+=
primitive("chardef", SHORTHAND_DEF, CHAR_DEF_CODE);
primitive("mathchardef", SHORTHAND_DEF, MATH_CHAR_DEF_CODE);
primitive("countdef", SHORTHAND_DEF, COUNT_DEF_CODE);
primitive("dimendef", SHORTHAND_DEF, DIMEN_DEF_CODE);
primitive("skipdef", SHORTHAND_DEF, SKIP_DEF_CODE);
primitive("muskipdef", SHORTHAND_DEF, MU_SKIP_DEF_CODE);
primitive("toksdef", SHORTHAND_DEF, TOKS_DEF_CODE);
```
