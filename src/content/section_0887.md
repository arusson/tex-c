# Section 887

The following code begins with *q* at the end of the list to be justified.
It ends with *q* at the beginning of that list, and with *link(TEMP_HEAD)* pointing to the remainder of the paragraph, if any.

```c << Put the \leftskip glue at the left and detach this line >>=
r = link(q);
link(q) = null;
q = link(TEMP_HEAD);
link(TEMP_HEAD) = r;
if (left_skip != ZERO_GLUE) {
    r = new_param_glue(LEFT_SKIP_CODE);
    link(r) = q;
    q = r;
}
```
