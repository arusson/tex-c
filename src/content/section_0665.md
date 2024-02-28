# Section 665

```c << Determine the shrink order >>=
if (total_shrink[FILLL] != 0) {
    o = FILLL;
}
else if (total_shrink[FILL] != 0) {
    o = FILL;
}
else if (total_shrink[FIL] != 0) {
    o = FIL;
}
else {
    o = NORMAL;
}
```
