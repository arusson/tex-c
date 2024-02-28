# Section 659

```c << Determine the stretch order >>=
if (total_stretch[FILLL] != 0) {
    o = FILLL;
}
else if (total_stretch[FILL] != 0) {
    o = FILL;
}
else if (total_stretch[FIL] != 0) {
    o = FIL;
}
else {
    o = NORMAL;
}
```
