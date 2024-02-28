# Section 275

Just before an entry of *eqtb* is changed, the following procedure should be called to update the other data structures properly.
It is important to keep in mind that reference counts in *mem* include references from within *save_stack*, so these counts must be handled carefully.

```c datastructures/stack.c
// gets ready to forget |w|
void eq_destroy(memory_word w) {
    pointer q; // |equiv| field of |w|
    switch(eq_type_field(w)) {
    case CALL:
    case LONG_CALL:
    case OUTER_CALL:
    case LONG_OUTER_CALL:
        delete_token_ref(equiv_field(w));
        break;

    case GLUE_REF:
        delete_glue_ref(equiv_field(w));
        break;

    case SHAPE_REF:
        q = equiv_field(w); // we need to free a \parshape block
        if (q != null) {
            // such a block is |2n+1| words long, where |n=info(q)|
            free_node(q, info(q) + info(q) + 1);
        }
        break;
    
    case BOX_REF:
        flush_node_list(equiv_field(w));
        break;
    
    default:
        do_nothing;
    }
}
```
