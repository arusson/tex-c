# Section 268: Saving and restoring equivalents

The nested structure provided by '`{...}`' groups in $\TeX$ means that *eqtb* entries valid in outer groups should be saved and restored later if they are overridden inside the braces.
When a new *eqtb* value is being assigned, the program therefore checks to see if the previous entry belongs to an outer level.
In such a case, the old value is placed on the *save_stack* just before the new value enters *eqtb*.
At the end of a grouping level, i.e., when the right brace is sensed, the *save_stack* is used to restore the outer values, and the inner ones are destroyed.

Entries on the *save_stack* are of type *memory_word*.
The top item on this stack is *save_stack[p]*, where *p = save_ptr − 1*;
it contains three fields called *save_type*, *save_level*, and *save_index*, and it is interpreted in one of four ways:

1. If *save_type(p) = RESTORE_OLD_VALUE*, then *save_index(p)* is a location in *eqtb*
   whose current value should be destroyed at the end of the current group and replaced
   by *save_stack[p − 1]*.
   Furthermore if *save_index(p) >= INT_BASE*, then *save_level(p)* should replace the
   corresponding entry in *xeq_level*.

2. If *save_type(p) = RESTORE_ZERO*, then *save_index(p)* is a location in *eqtb* whose
   current value should be destroyed at the end of the current group, when it should be
   replaced by the value of *eqtb[UNDEFINED_CONTROL_SEQUENCE]*.

3. If *save_type(p) = INSERT_TOKEN*, then *save_index(p)* is a token that should be
   inserted into $\TeX$'s input when the current group ends.

4. If *save_type(p) = LEVEL_BOUNDARY*, then *save_level(p)*
   is a code explaining what kind of group we were previously in, and
   *save_index(p)* points to the level boundary word at the bottom of
   the entries for that group.

```c include/constants.h
#define RESTORE_OLD_VALUE 0 // |save_type| when a value should be restored later
#define RESTORE_ZERO      1 // |save_type| when an undefined entry should be restored
#define INSERT_TOKEN      2 // |save_type| when a token is being saved for later use
#define LEVEL_BOUNDARY    3 // |save_type| corresponding to beginning of group
```

```c include/datastructures.h
#define save_type(X)  hh_b0(save_stack[(X)]) // classifies a |save_stack| entry
#define save_level(X) hh_b1(save_stack[(X)]) // saved level for regions 5 and 6, or group code
#define save_index(X) hh_rh(save_stack[(X)]) // |eqtb| location or token or |save_stack| location
```
