# Section 216

When $\TeX$'s work on one level is interrupted, the state is saved by calling *push_nest*.
This routine changes *head* and *tail* so that a new (empty) list is begun; it does not change *mode* or *aux*.

```c datastructures/modes.c
// << Start file |modes.c| >>

// enter a new semantic level, save the old
void push_nest() {
    if (nest_ptr > max_nest_stack) {
        max_nest_stack = nest_ptr;
        if (nest_ptr == NEST_SIZE) {
            overflow("semantic nest size", NEST_SIZE);
        }
    }
    nest[nest_ptr] = cur_list; // stack the record
    incr(nest_ptr);
    head = get_avail();
    tail = head;
    prev_graf = 0;
    mode_line = line;
}
```
