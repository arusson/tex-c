# Section 865

```c << Clean up the memory by removing the break nodes >>=
q = link(ACTIVE);
while (q != LAST_ACTIVE) {
    cur_p = link(q);
    if (type(q) == DELTA_NODE) {
        free_node(q, DELTA_NODE_SIZE);
    }
    else {
        free_node(q, ACTIVE_NODE_SIZE);
    }
    q = cur_p;
}
q = passive;
while (q != null) {
    cur_p = link(q);
    free_node(q, PASSIVE_NODE_SIZE);
    q = cur_p;
}
```
