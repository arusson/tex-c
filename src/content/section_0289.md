# Section 289: Token lists

A $\TeX$ token is either a character or a control sequence, and it is represented internally in one of two ways: (1)&nbsp;A character whose ASCII code number is *c* and whose command code is *m* is represented as the number $2^8$*m + c*; the command code is in the range *1* $\leq$ *m* $\leq$ *14*.
(2)&nbsp;A control sequence whose *eqtb* address is *p* is represented as the number *CS_TOKEN_FLAG + p*.
Here *CS_TOKEN_FLAG* = $2^{12} - 1$ is larger than $2^8$*m + c*, yet it is small enough that *CS_TOKEN_FLAG* + *p* $<$ *MAX_HALFWORD*;
thus, a token fits comfortably in a halfword.

A token *t* represents a *LEFT_BRACE* command if and only if *t* $<$ *LEFT_BRACE_LIMIT*;
it represents a *RIGHT_BRACE* command if and only if we have *LEFT_BRACE_LIMIT* $\leq$ *t* $<$ *RIGHT_BRACE_LIMIT*;
and it represents a *MATCH* or *END_MATCH* command if and only if *MATCH_TOKEN* $\leq$ *t* $\leq$ *END_MATCH_TOKEN*.
The following definitions take care of these token-oriented constants and a few others.

```c include/constants.h
#define CS_TOKEN_FLAG      0xfff  // amount added to the |eqtb| location in a token that stands for a control sequence; is a multiple of 256, less 1
#define LEFT_BRACE_TOKEN   0x100  // 2^8 * |LEFT_BRACE|
#define LEFT_BRACE_LIMIT   0x200  // 2^8 * (|LEFT_BRACE| + 1)
#define RIGHT_BRACE_TOKEN  0x200  // 2^8 * |RIGHT_BRACE|
#define RIGHT_BRACE_LIMIT  0x300  // 2^8 * (|RIGHT_BRACE| + 1)
#define MATH_SHIFT_TOKEN   0x300  // 2^8 * |MATH_SHIFT|
#define TAB_TOKEN          0x400  // 2^8 * |TAB_MARK|
#define OUT_PARAM_TOKEN    0x500  // 2^8 * |OUT_PARAM|
#define SPACE_TOKEN        0xa20  // 2^8 * |SPACER| + |' '|
#define LETTER_TOKEN       0xb00  // 2^8 * |LETTER|
#define OTHER_TOKEN        0xc00  // 2^8 * |OTHER_CHAR|
#define MATCH_TOKEN        0xd00  // 2^8 * |MATCH|
#define END_MATCH_TOKEN    0xe00  // 2^8 * |END_MATCH|
```
