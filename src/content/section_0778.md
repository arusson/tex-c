# Section 778

```c << Append the current tabskip glue to the preamble list >>=
link(cur_align) = new_param_glue(TAB_SKIP_CODE);
cur_align = link(cur_align);
```
