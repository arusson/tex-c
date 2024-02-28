# Section 787

The parameter to *init_span* is a pointer to the alignrecord where the next column or group of columns will begin.
A new semantic level is entered, so that the columns will generate a list for subsequent packaging.

```c alignment.c
void init_span(pointer p) {
    push_nest();
    if (mode == -HMODE) {
        space_factor = 1000;
    }
    else {
        prev_depth = IGNORE_DEPTH;
        normal_paragraph();
    }
    cur_span = p;
}
```
