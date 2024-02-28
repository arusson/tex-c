# Section 802

```c << Nullify |width(q)| and the tabskip glue following this column >>=
width(q) = 0;
r = link(q);
s = glue_ptr(r);
if (s != ZERO_GLUE) {
    add_glue_ref(ZERO_GLUE);
    delete_glue_ref(s);
    glue_ptr(r) = ZERO_GLUE;
}
```
