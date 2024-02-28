# Section 496

```c << Pop the condition stack >>=
p = cond_ptr;
if_line = if_line_field(p);
cur_if = subtype(p);
if_limit = type(p);
cond_ptr = link(p);
free_node(p, IF_NODE_SIZE);
```
