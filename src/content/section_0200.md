# Section 200

First, however, we shall consider two non-recursive procedures that do simpler tasks. The first of these, *delete_token_ref*, is called when a pointer to a token list's reference count is being removed.
This means that the token list should disappear if the reference count was *null*, otherwise the count should be decreased by one.

```c include/datastructures.h
#define token_ref_count(X) info((X)) // reference count preceding a token list
```

```c datastructures/memory.c
// |p| points to the reference count of a token list that is losing one reference
void delete_token_ref(pointer p) {
    if (token_ref_count(p) == null) {
        flush_list(p);
    }
    else {
        decr(token_ref_count(p));
    }
}
```
