# Section 165

If $\TeX$ is extended improperly, the *mem* array might get screwed up.
For example, some pointers might be wrong, or some "dead" nodes might not have been freed when the last reference to them disappeared.
Procedures *check_mem* and *search_mem* are available to help diagnose such problems.
These procedures make use of two arrays called *is_free* and *was_free* that are present only if $\TeX$'s debugging routines have been included. (You may want to decrease the size of *mem* while you
are debugging.)

> ![NOTE]
> The *free* array has been renamed *free_cells* since *"free"* is a reserved word in C.

```c << Global variables >>+=
#ifdef DEBUG
bool free_cells[MEM_MAX + 1]; // free_cells
bool was_free[MEM_MAX + 1];   // previously free cells
pointer was_mem_end, was_lo_max, was_hi_min; // previous |mem_end|, |lo_mem_max|, and |hi_mem_min|
bool panicking; // do we want to check memory constantly?
#endif
```
