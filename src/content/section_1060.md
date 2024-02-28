# Section 1060

All the work relating to glue creation has been relegated to the following subroutine.
It does not call *build_page*, because it is used in at least one place where that would be a mistake.

```c builder/boxes_and_lists.c
// << Start file |boxes_and_lists.c| >>

void append_glue() {
    small_number s; // modifier of skip command
    s = cur_chr;
    switch (s) {
    case FIL_CODE:
        cur_val = FIL_GLUE;
        break;
    
    case FILL_CODE:
        cur_val = FILL_GLUE;
        break;
    
    case SS_CODE:
        cur_val = SS_GLUE;
        break;
    
    case FIL_NEG_CODE:
        cur_val = FIL_NEG_GLUE;
        break;
    
    case SKIP_CODE:
        scan_glue(GLUE_VAL);
        break;
    
    case MSKIP_CODE:
        scan_glue(MU_VAL);
    } // now |cur_val| points to the glue specification
    tail_append(new_glue(cur_val));
    if (s >= SKIP_CODE) {
        decr(glue_ref_count(cur_val));
        if (s > SKIP_CODE) {
            subtype(tail) = MU_GLUE;
        }
    }
}
```
