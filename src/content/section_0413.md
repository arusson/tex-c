# Section 413

OK, we're ready for *scan_something_internal* itself.
A second parameter, *negative*, is set *true* if the value that is found should be negated.
It is assumed that *cur_cmd* and *cur_chr* represent the first token of the internal quantity to be scanned; an error will be signalled if *cur_cmd* $<$ *MIN_INTERNAL* or *cur_cmd* $>$ *MAX_INTERNAL*.

```c include/parser.h
#define scanned_result(X, Y) \
    cur_val = (X);           \
    cur_val_level = (Y)
```

```c parser/subroutines.c
// fetch an internal parameter
void scan_something_internal(small_number level, bool negative) {
    halfword m; // |chr_code| part of the operand token
    int p;      // index into |nest|
    m = cur_chr;
    switch (cur_cmd) {
    case DEF_CODE:
        // << Fetch a character code from some table >>
        break;
    
    case TOKS_REGISTER:
    case ASSIGN_TOKS:
    case DEF_FAMILY:
    case SET_FONT:
    case DEF_FONT:
        // << Fetch a token list or font identifier, provided that |level = TOK_VAL| >>
        break;
    
    case ASSIGN_INT:
        scanned_result(eqtb[m].integer, INT_VAL);
        break;
    
    case ASSIGN_DIMEN:
        scanned_result(eqtb[m].sc, DIMEN_VAL);
        break;
    
    case ASSIGN_GLUE:
        scanned_result(equiv(m), GLUE_VAL);
        break;
    
    case ASSIGN_MU_GLUE:
        scanned_result(equiv(m), MU_VAL);
        break;
    
    case SET_AUX:
        // << Fetch the |space_factor| or the |prev_depth| >>
        break;
    
    case SET_PREV_GRAF:
        // << Fetch the |prev_graf| >>
        break;
    
    case SET_PAGE_INT:
        // << Fetch the |dead_cycles| or the |insert_penalties| >>
        break;
    
    case SET_PAGE_DIMEN:
        // << Fetch something on the |page_so_far| >>
        break;
    
    case SET_SHAPE:
        // << Fetch the |par_shape| size >>
        break;
    
    case SET_BOX_DIMEN:
        // << Fetch a box dimension >>
        break;
    
    case CHAR_GIVEN:
    case MATH_GIVEN:
        scanned_result(cur_chr, INT_VAL);
        break;
    
    case ASSIGN_FONT_DIMEN:
        // << Fetch a font dimension >>
        break;
    
    case ASSIGN_FONT_INT:
        // << Fetch a font integer >>
        break;
    
    case REGISTER:
        // << Fetch a register >>
        break;
    
    case LAST_ITEM:
        // << Fetch an item in the current node, if appropriate >>
        break;
    
    default:
        // << Complain that \the can't do this; give zero result >>
    }
    while (cur_val_level > level) {
        // << Convert |cur_val| to a lower level >>
    }
    // << Fix the reference count, if any, and negate |cur_val| if |negative| >>
}
```
