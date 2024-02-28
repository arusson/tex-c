# Section 203: Copying boxes

Another recursive operation that acts on boxes is sometimes needed:
Theprocedure *copy_node_list* returns a pointer to another node list that has the same structure and meaning as the original.
Note that since glue specifications and token lists have reference counts, we need not make copies of them.
Reference counts can never get too large to fit in a halfword, since each pointer to a node is in a different memory address, and the total number of memory addresses fits in a halfword.

(Well, there actually are also references from outside *mem*; if the *save_stack* is made arbitrarily large, it would theoretically be possible to break $\TeX$ by overflowing a reference count.
But who would want to do that?)

```c include/datastructures.h
#define add_token_ref(X) incr(token_ref_count((X))) // new reference to a token list
#define add_glue_ref(X)  incr(glue_ref_count((X)))  // new reference to a glue spec
```
