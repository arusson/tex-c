# Section 274

Procedure *new_save_level* is called when a group begins.
The argument is a group identification code like *'HBOX_GROUP'*.
After calling this routine, it is safe to put five more entries on *save_stack*.

In some cases integer-valued items are placed onto the *save_stack* just below a *LEVEL_BOUNDARY* word, because this is a convenient place to keep information that is supposed to "pop up" just when the group has finished.
For example, when '`\hbox to 100pt{...}`' is being treated, the 100pt dimension is stored on *save_stack* just before *new_save_level* is called.

We use the notation *saved(k)* to stand for an integer item that appears in location *save_ptr + k* of the save stack.

```c include/datastructures.h
#define saved(X) save_stack[save_ptr + (X)].integer
```

```c datastructures/stack.c
// << Start file |stack.c| >>

// begin a new level of grouping
void new_save_level(int c) {
    check_full_save_stack;
    save_type(save_ptr) = LEVEL_BOUNDARY;
    save_level(save_ptr) = cur_group;
    save_index(save_ptr) = cur_boundary;
    if (cur_level == MAX_QUARTERWORD) {
        overflow("grouping levels", MAX_QUARTERWORD - MIN_QUARTERWORD);
    } // quit if |(cur_level + 1)| is too big to be stored in |eqtb|
    cur_boundary = save_ptr;
    incr(cur_level);
    incr(save_ptr);
    cur_group = c;
}
```
