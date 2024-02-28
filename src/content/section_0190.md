# Section 190

```c << Display leaders |p| >>
if (subtype(p) == C_LEADERS) {
    print_esc("cleaders ");
}
else if (subtype(p) == X_LEADERS) {
    print_esc("xleaders ");
}
else {
    print_esc("leaders ");
}
print_spec(glue_ptr(p), "");
node_list_display(leader_ptr(p)); // recursive call
```
