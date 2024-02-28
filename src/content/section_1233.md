# Section 1233

```c << Let |n| be the largest legal code value, based on |cur_chr| >>=
if (cur_chr == CAT_CODE_BASE) {
    n = MAX_CHAR_CODE;
}
else if (cur_chr == MATH_CODE_BASE) {
    n = 0x8000;
}
else if (cur_chr == SF_CODE_BASE) {
    n = 0x7fff;
}
else if (cur_chr == DEL_CODE_BASE) {
    n = 0xffffff;
}
else {
    n = 255;
}
```
