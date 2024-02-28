# Section 201

Similarly, *delete_glue_ref* is called when a pointer to a glue specification is being withdrawn.

```c include/datastructures.h
#define fast_delete_glue_ref(X)             \
    do {                                    \
        if (glue_ref_count((X)) == null) {  \
            free_node((X), GLUE_SPEC_SIZE); \
        }                                   \
        else {                              \
            decr(glue_ref_count((X)));      \
        }                                   \
    } while (0)
```

```c datastructures/memory.c
// |p| points to a glue specification
void delete_glue_ref(pointer p) {
    fast_delete_glue_ref(p);
}
```
