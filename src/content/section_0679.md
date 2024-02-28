# Section 679

When a box is being appended to the current vertical list, the baselineskip calculation is handled by the *append_to_vlist* routine.

```c builder/packaging.c
void append_to_vlist(pointer b) {
    scaled d; // deficiency of space between baselines
    pointer p; // a new glue node
    if (prev_depth > IGNORE_DEPTH) {
        d = width(baseline_skip) - prev_depth - height(b);
        if (d < line_skip_limit) {
            p = new_param_glue(LINE_SKIP_CODE);
        }
        else {
            p = new_skip_param(BASELINE_SKIP_CODE);
            width(temp_ptr) = d; // |temp_ptr = glue_ptr(p)|
        }
        link(tail) = p;
        tail = p;
    }
    link(tail) = b;
    tail = b;
    prev_depth = depth(b);
}
```
