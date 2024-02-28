# Section 838

```c << Subtract glue from |break_width| >>=
v = glue_ptr(s);
break_width[1] -= width(v);
break_width[2 + stretch_order(v)] -= stretch(v);
break_width[6] -= shrink(v);
```
