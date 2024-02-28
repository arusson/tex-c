# Section 283

A global definition, which sets the level to *LEVEL_ONE*, will not be undone by *unsave*.
If at least one global definition of *eqtb[p]* has been carried out within the group that just ended, the last such definition will therefore survive.

```c << Store |save_stack[save_ptr]| in |eqtb[p]|, unless |eqtb[p]| holds a global value >>=
if (p < INT_BASE) {
    if (eq_level(p) == LEVEL_ONE) {
        eq_destroy(save_stack[save_ptr]); // destroy the saved value
#ifdef STAT        
        if (tracing_restores > 0) {
            restore_trace(p, "retaining");
        }
#endif
    }
    else {
        eq_destroy(eqtb[p]); // destroy the current value
        eqtb[p] = save_stack[save_ptr]; // restore the saved value
#ifdef STAT
        if (tracing_restores > 0) {
            restore_trace(p, "restoring");
        }
#endif
    }
}
else if (xeq_level[p] != LEVEL_ONE) {
    eqtb[p] = save_stack[save_ptr];
    xeq_level[p] = l;
#ifdef STAT
    if (tracing_restores > 0) {
        restore_trace(p, "restoring");
    }
#endif
}
#ifdef STAT
else {
  if (tracing_restores > 0) {
    restore_trace(p, "retaining");
  }
}
#endif
```
