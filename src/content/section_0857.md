# Section 857

```c << Print the list between |printed_node| and |cur_p|, then set |printed_node = cur_p| >>=
print_nl("");
if (cur_p == null) {
    short_display(link(printed_node));
}
else {
    save_link = link(cur_p);
    link(cur_p) = null;
    print_nl("");
    short_display(link(printed_node));
    link(cur_p) = save_link;
}
printed_node = cur_p;
```
