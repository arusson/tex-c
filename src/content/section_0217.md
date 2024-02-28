# Section 217

Conversely, when $\TeX$ is finished on the current level, the former state is restored by calling *pop_nest*.
This routine will never be called at the lowest semantic level, nor will it be called unless *head* is a node that should be returned to free memory.

```c datastructures/modes.c
// leave a semantic level, re-enter the old
void pop_nest() {
    free_avail(head);
    decr(nest_ptr);
    cur_list = nest[nest_ptr];
}
```
