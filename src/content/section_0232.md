# Section 232

We initialize most things to null or undefined values. An undefined font is represented by the internal code *FONT_BASE*.

However, the character code tables are given initial values based on the conventional interpretation of ASCII code.
These initial values should not be changed when $\TeX$ is adapted for use with non-English languages;
all changes to the initialization conventions should be made in format packages, not in $\TeX$ itself, so that global interchange of formats is possible.

```c include/constants.h
#define NULL_FONT FONT_BASE
#define VAR_CODE 0x7000 // math code meaning "use the current family"
```

```c << Initialize table entries (done by INITEX only) >>+=
par_shape_ptr = null;
eq_type(PAR_SHAPE_LOC) = SHAPE_REF;
eq_level(PAR_SHAPE_LOC) = LEVEL_ONE;
for(k = OUTPUT_ROUTINE_LOC; k <= TOKS_BASE + 255; k++) {
    eqtb[k] = eqtb[UNDEFINED_CONTROL_SEQUENCE];
}
box(0) = null;
eq_type(BOX_BASE) = BOX_REF;
eq_level(BOX_BASE) = LEVEL_ONE;
for(k = BOX_BASE + 1; k <= BOX_BASE + 255; k++) {
    eqtb[k] = eqtb[BOX_BASE];
}
cur_font = NULL_FONT;
eq_type(CUR_FONT_LOC) = DATA;
eq_level(CUR_FONT_LOC) = LEVEL_ONE;
for(k = MATH_FONT_BASE; k <= MATH_FONT_BASE + 47; k++) {
    eqtb[k] = eqtb[CUR_FONT_LOC];
}
equiv(CAT_CODE_BASE) = 0;
eq_type(CAT_CODE_BASE) = DATA;
eq_level(CAT_CODE_BASE) = LEVEL_ONE;
for(k = CAT_CODE_BASE + 1; k <= INT_BASE - 1; k++) {
    eqtb[k] = eqtb[CAT_CODE_BASE];
}
for(k = 0; k <= 255; k++) {
    cat_code(k) = OTHER_CHAR;
    math_code(k) = hi(k);
    sf_code(k) = 1000;
}
cat_code(CARRIAGE_RETURN) = CAR_RET;
cat_code(' ') = SPACER;
cat_code('\\') = ESCAPE;
cat_code('%') = COMMENT;
cat_code(INVALID_CODE) = INVALID_CHAR;
cat_code(NULL_CODE) = IGNORE;
for(k = '0'; k <= '9'; k++) {
    math_code(k) = hi(k + VAR_CODE);
}
for(k = 'A'; k <= 'Z'; k++) {
    cat_code(k) = LETTER;
    cat_code(k + 'a' - 'A') = LETTER;
    math_code(k) = hi(k + VAR_CODE + 0x100);
    math_code(k + 'a' - 'A') = hi(k + 'a' - 'A' + VAR_CODE + 0x100);
    lc_code(k) = k + 'a' - 'A';
    lc_code(k + 'a' - 'A') = k + 'a' - 'A';
    uc_code(k) = k;
    uc_code(k + 'a' - 'A') = k;
    sf_code(k) = 999;
}
```
