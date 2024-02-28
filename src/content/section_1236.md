# Section 1236

We use the fact that *REGISTER* $<$ *ADVANCE* $<$ *MULTIPLY* $<$ *DIVIDE*.

```c << Declare subprocedures for |prefixed_command| >>+=
void do_register_command(small_number a) {
    pointer l, q, r, s; // for list manipulation
    int p;              // type of register involved
    l = null;
    q = cur_cmd;
    // << Compute the register location |l| and its type |p|; but |return| if invalid >>
    if (q == REGISTER) {
        scan_optional_equals();
    }
    else {
        scan_keyword("by"); // do nothing, optional "by"
    }
    arith_error = false;
    if (q < MULTIPLY) {
        // << Compute result of |REGISTER| or |ADVANCE|, put it in |cur_val| >>
    }
    else {
        // << Compute result of |MULTIPLY| or |DIVIDE|, put it in |cur_val| >>
    }
    if (arith_error) {
        print_err("Arithmetic overflow");
        help2("I can't carry out that multiplication or division,")
            ("since the result is out of range.");
        if (p >= GLUE_VAL) {
            delete_glue_ref(cur_val);
        }
        error();
        return;
    }
    if (p < GLUE_VAL) {
        word_define(l, cur_val);
    }
    else {
        trap_zero_glue();
        define(l, GLUE_REF, cur_val);
    }
}
```
