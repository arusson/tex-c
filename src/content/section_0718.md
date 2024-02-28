# Section 718

Sometimes it is necessary to destroy an mlist.
The following subroutine empties the current list, assuming that *abs(mode) = MMODE*.

```c math/math_subroutines.c
void flush_math() {
    flush_node_list(link(head));
    flush_node_list(incompleat_noad);
    link(head) = null;
    tail = head;
    incompleat_noad = null;
}
```
