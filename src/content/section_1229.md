# Section 1229

When a glue register or parameter becomes zero, it will always point to *ZERO_GLUE* because of the following procedure.
(Exception: The tabskip glue isn't trapped while preambles are being scanned.)

```c << Declare subprocedures for |prefixed_command| >>+=
void trap_zero_glue() {
    if (width(cur_val) == 0
        && stretch(cur_val) == 0
        && shrink(cur_val) == 0)
    {
        add_glue_ref(ZERO_GLUE);
        delete_glue_ref(cur_val);
        cur_val = ZERO_GLUE;
    }
}
```
