# Section 886

```c << Put the \rightskip glue after node |q| >>=
r = new_param_glue(RIGHT_SKIP_CODE);
link(r) = link(q);
link(q) = r;
q = r;
```
