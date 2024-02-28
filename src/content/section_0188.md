# Section 188

```c << Display insertion |p| >>=
print_esc("insert");
print_int(subtype(p));
print(", natural size ");
print_scaled(height(p));
print("; split(");
print_spec(split_top_ptr(p), "");
print_char(',');
print_scaled(depth(p));
print("); float cost ");
print_int(float_cost(p));
node_list_display(ins_ptr(p)); // recursive call
```
