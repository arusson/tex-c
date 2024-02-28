# Section 826

```c << Declare subprocedures for |line_break| >>=
// recovers from infinite shrinkage
pointer finite_shrink(pointer p) {
    pointer q; // new glue specification
    if (no_shrink_error_yet) {
        no_shrink_error_yet = false;
#ifdef STAT
        if (tracing_paragraphs > 0) {
            end_diagnostic(true);
        }
#endif
        print_err("Infinite glue shrinkage found in a paragraph");
        help5("The paragraph just ended includes some glue that has")
            ("infinite shrinkability, e.g., `\\hskip 0pt minus 1fil'.")
            ("Such glue doesn't belong there---it allows a paragraph")
            ("of any length to fit on one line. But it's safe to proceed,")
            ("since the offensive shrinkability has been made finite.");
        error();
#ifdef STAT
        if (tracing_paragraphs > 0) {
            begin_diagnostic();
        }
#endif
    }
    q = new_spec(p);
    shrink_order(q) = NORMAL;
    delete_glue_ref(p);
    return q;
}
```
