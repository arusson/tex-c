# Section 121

Conversely, a one-word node is recycled by calling *free_avail*.
This routine is part of $\TeX$'s "inner loop", so we want it to be fast.

```c include/datastructures.h
// single-word node liberation
#ifdef STAT
#define decr_dyn_used decr(dyn_used)
#define incr_dyn_used incr(dyn_used)
#else
#define decr_dyn_used
#define incr_dyn_used
#endif

#define free_avail(X) link((X)) = avail; avail = (X); decr_dyn_used
```
