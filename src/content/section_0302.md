# Section 302

We've already defined the special variable *loc = cur_input.loc_field* in our discussion of basic input-output routines.
The other components of *cur_input* are defined in the same way:

```c include/datastructures.h
#define state cur_input.state_field // current scanner state
#define index cur_input.index_field // reference for buffer information
#define start cur_input.start_field // starting position in |buffer|
#define limit cur_input.limit_field // end of current line in |buffer|
#define name  cur_input.name_field  // name of the current file
```
