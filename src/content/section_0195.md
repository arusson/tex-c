# Section 195

The *post_break* list of a discretionary node is indicated by a prefixed '`|`' instead of the '`.`' before the *pre_break* list.

```c << Display discretionary |p| >>=
print_esc("discretionary");
if (replace_count(p) > 0) {
    print(" replacing ");
    print_int(replace_count(p));
}
node_list_display(pre_break(p)); // recursive call
append_char('|');
show_node_list(post_break(p)); // recursive call
flush_char;
```
