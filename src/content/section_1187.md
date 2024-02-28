# Section 1187

```c << Replace the tail of the list by |p| >>=
q = head;
while (link(q) != tail) {
    q = link(q);
}
link(q) = p;
free_node(tail, NOAD_SIZE);
tail = p;
```
