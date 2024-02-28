# Section 630

```c << Output node |p| for |vlist_out| and move to the next node, maintaining the condition |cur_h = left_edge| >>=
if (is_char_node(p)) {
    confusion("vlistout");
}
else {
    // << Output the non-|CHAR_NODE| |p| for |vlist_out| >>
}
next_p:
p = link(p);
```
