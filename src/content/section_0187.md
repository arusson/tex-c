# Section 187

```c << Display rule |p| >>=
print_esc("rule(");
print_rule_dimen(height(p));
print_char('+');
print_rule_dimen(depth(p));
print(")x");
print_rule_dimen(width(p));
```
