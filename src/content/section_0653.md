# Section 653

The code here implicitly uses the fact that running dimensions are indicated by *NULL_FLAG*, which will be ignored in the calculations because it is a highly negative number.

```c << Incorporate box dimensions into the dimensions of the hbox that will contain it >>=
x += width(p);
if (type(p) >= RULE_NODE) {
    s = 0;
}
else {
    s = shift_amount(p);
}
if (height(p) - s > h) {
    h = height(p) - s;
}
if (depth(p) + s > d) {
    d = depth(p) + s;
}
```
