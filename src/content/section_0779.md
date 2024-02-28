# Section 779

```c << Scan preamble text until |cur_cmd| is |TAB_MARK| or |CAR_RET|, looking for changes in the tabskip glue; append an alignrecord to the preamble list >>=
// << Scan the template <u_j>, putting the resulting token list in |HOLD_HEAD| >>
link(cur_align) = new_null_box();
cur_align = link(cur_align); // a new alignrecord
info(cur_align) = END_SPAN;
width(cur_align) = NULL_FLAG;
u_part(cur_align) = link(HOLD_HEAD);
// << Scan the template <v_j>, putting the resulting token list in |HOLD_HEAD| >>
v_part(cur_align) = link(HOLD_HEAD);
```
