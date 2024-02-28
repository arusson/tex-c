# Section 795

```c << Copy the tabskip glue between columns >>=
tail_append(new_glue(glue_ptr(link(cur_align))));
subtype(tail) = TAB_SKIP_CODE + 1;
```
