# Section 154

Still another subroutine is needed:
This one is sort of a combination of *new_param_glue* and *new_glue*.
It creates a glue node for one of the current glue parameters, but it makes a fresh copy of the glue specification, since that specification will probably be subject to change, while the parameter will stay put.
The global variable *temp_ptr* is set to the address of the new spec.

```c datastructures/nodes.c
pointer new_skip_param(small_number n) {
    pointer p; // the new node
    temp_ptr = new_spec(glue_par(n));
    p = new_glue(temp_ptr);
    glue_ref_count(temp_ptr) = null;
    subtype(p) = n + 1;
    return p;
}
```
