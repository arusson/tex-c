# Section 670

```c << Incorporate box dimensions into the dimensions of the vbox that will contain it >>=
x += d + height(p);
d = depth(p);
if (type(p) >= RULE_NODE) {
    s = 0;
}
else {
    s = shift_amount(p);
}
if (width(p) + s > w) {
    w = width(p) + s;
}
```
