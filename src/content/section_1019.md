# Section 1019

```c << Delete the page-insertion nodes >>=
r = link(PAGE_INS_HEAD);
while (r != PAGE_INS_HEAD) {
    q = link(r);
    free_node(r, PAGE_INS_NODE_SIZE);
    r = q;
}
link(PAGE_INS_HEAD) = PAGE_INS_HEAD;
```
