# Section 786

To start a row (i.e., a 'row' that rhymes with 'dough' but not with 'bough'), we enter a new semantic level, copy the first tabskip glue, and change from internal vertical mode to restricted horizontal mode or vice versa.
The *space_factor* and *prev_depth* are not used on this semantic level, but we clear them to zero just to be tidy.

```c alignment.c
void init_row() {
    push_nest();
    mode = (-HMODE - VMODE) - mode;
    if (mode == -HMODE) {
        space_factor = 0;
    } 
    else {
        prev_depth = 0;
    }
    tail_append(new_glue(glue_ptr(preamble)));
    subtype(tail) = TAB_SKIP_CODE + 1;
    cur_align = link(preamble);
    cur_tail = cur_head;
    init_span(cur_align);
}
```
