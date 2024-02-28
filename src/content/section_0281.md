# Section 281

The *unsave* routine goes the other way, taking items off of *save_stack*.
This routine takes care of restoration when a level ends; everything belonging to the topmost group is cleared off of the save stack.

```c datastructures/stack.c
// << Declare the procedure called |restore_trace| >>

// pops the top level off the save stack
void unsave() {
    pointer p;         // position to be restored
    quarterword l = 0; // saved level, if in fullword regions of |eqtb|
    halfword t;        // saved value of |cur_tok|
    if (cur_level > LEVEL_ONE) {
        decr(cur_level);
        // << Clear off top level from |save_stack| >>
    }
    else {
        // |unsave| is not used when |cur_group=bottom_level|
        confusion("curlevel");
    }
}
```
