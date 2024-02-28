# Section 999

```c << Recycle node |p| >>=
link(CONTRIB_HEAD) = link(p);
link(p) = null;
flush_node_list(p);
```
