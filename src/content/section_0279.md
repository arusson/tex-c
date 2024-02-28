# Section 279

The *eq_define* and *eq_word_define* routines take care of local definitions.
Global definitions are done in almost the same way, but there is no need to save old values, and the new value is associated with *LEVEL_ONE*.

```c datastructures/stack.c
// global |eq_define|
void geq_define(pointer p, quarterword t, halfword e) {
    eq_destroy(eqtb[p]);
    eq_level(p) = LEVEL_ONE;
    eq_type(p) = t;
    equiv(p) = e;
}

// global |eq_word_define|
void geq_word_define(pointer p, int w) {
    eqtb[p].integer = w;
    xeq_level[p] = LEVEL_ONE;
}
```
