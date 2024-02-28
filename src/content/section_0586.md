# Section 586

```c include/constants.h
#define SET_CHAR_0 0   // typeset character 0 and move right
#define SET1       128 // typeset a character and move right
#define SET_RULE   132 // typeset a rule and move right
#define PUT_RULE   137 // typeset a rule
#define NOP        138 // no operation
#define BOP        139 // beginning of page
#define EOP        140 // ending of page
#define PUSH       141 // save the current positions
#define POP        142 // restore previous positions
#define RIGHT1     143 // move right
#define W0         147 // move right by |w|
#define W1         148 // move right and set |w|
#define X0         152 // move right by |x|
#define X1         153 // move right and set |x|
#define DOWN1      157 // move down
#define Y0         161 // move down by |y|
#define Y1         162 // move down and set |y|
#define Z0         166 // move down by |z|
#define Z1         167 // move down and set |z|
#define FNT_NUM_0  171 // set current font to 0
#define FNT1       235 // set current font
#define XXX1       239 // extension to `DVI` primitives
#define XXX4       242 // potentially long extension to `DVI` primitives
#define FNT_DEF1   243 // define the meaning of a font number
#define PRE        247 // preamble
#define POST       248 // postamble beginning
#define POST_POST  249 // postamble ending
```
