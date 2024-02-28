# Section 693

The inelegant introduction of *show_info* in the code above seems better than the alternative of using Pascal's strange *forward* declaration for a procedure with parameters.
The Pascal convention about dropping parameters from a post-*forward* procedure is, frankly, so intolerable to the author of $\TeX$ that he would rather stoop to communication via a global temporary variable.
(A similar stoopidity occurred with respect to *hlist_out* and *vlist_out* above, and it will occur with respect to *mlist_to_hlist* below.)

```c io/display_math.c
// the reader will kindly forgive this
void show_info() {
    show_node_list(info(temp_ptr));
}
```
