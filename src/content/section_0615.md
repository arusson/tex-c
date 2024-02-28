# Section 615

In case you are wondering when all the movement nodes are removed from $\TeX$'s memory, the answer is that they are recycled just before *hlist_out* and *vlist_out* finish outputting a box.
This restores the down and right stacks to the state they were in before the box was output, except that some *info*'s may have become more restrictive.

```c dvi.c
// delete movement nodes with |location >= l|
void prune_movements(int l) {
    pointer p; // node being deleted
    while (down_ptr != null) {
        if (location(down_ptr) < l) {
            break; // goto done
        }
        p = down_ptr;
        down_ptr = link(p);
        free_node(p, MOVEMENT_NODE_SIZE);
    }
    // done:
    while (right_ptr != null) {
        if (location(right_ptr) < l) {
            break; // return
        }
        p = right_ptr;
        right_ptr = link(p);
        free_node(p, MOVEMENT_NODE_SIZE);
    }
}
```
