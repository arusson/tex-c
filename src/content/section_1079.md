# Section 1079

Now that we can see what eventually happens to boxes, we can consider the first steps in their creation.
The *begin_box* routine is called when *box_context* is a context specification, *cur_chr* specifies the type of box desired, and *cur_cmd = MAKE_BOX*.

```c builder/boxes_and_lists.c
void begin_box(int box_context) {
    pointer p, q; // run through the current list
    int m;        // the length of a replacement list
    halfword k;   // 0 or |VMODE| or |HMODE|
    eight_bits n; // a box number
    
    switch (cur_chr) {
    case BOX_CODE:
        scan_eight_bit_int();
        cur_box = box(cur_val);
        box(cur_val) = null; // the box becomes void, at the same level
        break;
    
    case COPY_CODE:
        scan_eight_bit_int();
        cur_box = copy_node_list(box(cur_val));
        break;
    
    case LAST_BOX_CODE:
        // << If the current list ends with a box node, delete it from the list and make |cur_box| point to it; otherwise set |cur_box = null| >>
        break;
    
    case VSPLIT_CODE:
        // << Split off part of a vertical box, make |cur_box| point to it >>
        break;
    
    default:
        // << Initiate the construction of an hbox or vbox, then |return| >>
    }
    box_end(box_context); // in simple cases, we use the box immediately
}
```
