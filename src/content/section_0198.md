# Section 198

The recursive machinery is started by calling *show_box*.

```c io/display_boxes.c
void show_box(pointer p) {
    // << Assign the values |depth_threshold = show_box_depth| and |breadth_max = show_box_breadth| >>
    if (breadth_max <= 0) {
        breadth_max = 5;
    }
    if (pool_ptr + depth_threshold >= POOL_SIZE) {
        depth_threshold = POOL_SIZE - pool_ptr - 1;
    } // now there's enough room for prefix string
    show_node_list(p); // the show starts at |p|
    print_ln();
}
```
