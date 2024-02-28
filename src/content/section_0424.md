# Section 424

Here is where `\lastpenalty`, `\lastkern`, and `\lastskip` are implemented.
The reference count for `\lastskip` will be updated later.

We also handle `\inputlineno` and `\badness` here, because they are legal in similar contexts.

```c << Fetch an item in the current node, if appropriate >>=
if (cur_chr > GLUE_VAL) {
    if (cur_chr == INPUT_LINE_NO_CODE) {
        cur_val = line;
    }
    else {
        cur_val = last_badness; // |cur_chr = BADNESS_CODE|
    }
    cur_val_level = INT_VAL;
}
else {
    if (cur_chr == GLUE_VAL) {
        cur_val = ZERO_GLUE;
    }
    else {
        cur_val = 0;
    }
    cur_val_level = cur_chr;
    if (!is_char_node(tail) && mode != 0) {
        switch (cur_chr) {
        case INT_VAL:
            if (type(tail) == PENALTY_NODE) {
                cur_val = penalty(tail);
            }
            break;
        
        case DIMEN_VAL:
            if (type(tail) == KERN_NODE) {
                cur_val = width(tail);
            }
            break;
        
        case GLUE_VAL:
            if (type(tail) == GLUE_NODE) {
                cur_val = glue_ptr(tail);
                if (subtype(tail) == MU_GLUE) {
                    cur_val_level = MU_VAL;
                }
            }
        } // there are no other cases
    }
    else if (mode == VMODE && tail == head) {
        switch (cur_chr) {
        case INT_VAL:
            cur_val = last_penalty;
            break;
        
        case DIMEN_VAL:
            cur_val = last_kern;
            break;

        case GLUE_VAL:
            if (last_glue != MAX_HALFWORD) {
                cur_val = last_glue;
            }
        } // there are no other cases
    }
}
```
