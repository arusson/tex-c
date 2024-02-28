# Section 695

```c << Display choice node |p| >>=
print_esc("mathchoice");
append_char('D');
show_node_list(display_mlist(p));
flush_char;
append_char('T');
show_node_list(text_mlist(p));
flush_char;
append_char('S');
show_node_list(script_mlist(p));
flush_char;
append_char('s');
show_node_list(script_script_mlist(p));
flush_char;
```
