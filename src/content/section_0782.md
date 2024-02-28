# Section 782

The preamble is copied directly, except that `\tabskip` causes a change to the tabskip glue, thereby possibly expanding macros that immediately follow it.
An appearance of `\span` also causes such an expansion.

Note that if the preamble contains '`\global\tabskip`', the '`\global`' token survives in the preamble and the '`\tabskip`' defines new tabskip glue (locally).

```c << Declare the procedure called |get_preamble_token| >>=
void get_preamble_token() {
restart:
    get_token();
    while (cur_chr == SPAN_CODE && cur_cmd == TAB_MARK) {
        get_token(); // this token will be expanded once
        if (cur_cmd > MAX_COMMAND) {
            expand();
            get_token();
        }
    }
    if (cur_cmd == ENDV) {
        fatal_error("(interwoven alignment preambles are not allowed)");
    }
    if (cur_cmd == ASSIGN_GLUE
        && cur_chr == GLUE_BASE + TAB_SKIP_CODE)
    {
        scan_optional_equals();
        scan_glue(GLUE_VAL);
        if (global_defs > 0) {
            geq_define(GLUE_BASE + TAB_SKIP_CODE, GLUE_REF, cur_val);
        }
        else {
            eq_define(GLUE_BASE + TAB_SKIP_CODE, GLUE_REF, cur_val);
        }
        goto restart;
    }
}
```
