# Section 772

Alignment stack maintenance is handled by a pair of trivial routines called *push_alignment* and *pop_alignment*.

```c alignment.c
// << Start file |alignment.c| >>

void push_alignment() {
    pointer p; // the new alignment stack node
    p = get_node(ALIGN_STACK_NODE_SIZE);
    link(p) = align_ptr;
    info(p) = cur_align;
    llink(p) = preamble;
    rlink(p) = cur_span;
    mem[p + 2].integer = cur_loop;
    mem[p + 3].integer = align_state;
    info(p + 4) = cur_head;
    link(p + 4) = cur_tail;
    align_ptr = p;
    cur_head = get_avail();
}

void pop_alignment() {
    pointer p; // the top alignment stack node
    free_avail(cur_head);
    p = align_ptr;
    cur_tail = link(p + 4);
    cur_head = info(p + 4);
    align_state = mem[p + 3].integer;
    cur_loop = mem[p + 2].integer;
    cur_span = rlink(p);
    preamble = llink(p);
    cur_align = info(p);
    align_ptr = link(p);
    free_node(p, ALIGN_STACK_NODE_SIZE);
}
```
