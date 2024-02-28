# Section 1185

```c << Compleat the incompleat noad >>=
math_type(denominator(incompleat_noad)) = SUB_MLIST;
info(denominator(incompleat_noad)) = link(head);
if (p == null) {
    q = incompleat_noad;
}
else {
    q = info(numerator(incompleat_noad));
    if (type(q) != LEFT_NOAD) {
        confusion("right");
    }
    info(numerator(incompleat_noad)) = link(q);
    link(q) = incompleat_noad;
    link(incompleat_noad) = p;
}
```
