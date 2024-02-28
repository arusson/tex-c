# Section 175

```c << Print a short indication of the contents of node |p| >>=
switch(type(p)) {
case HLIST_NODE:
case VLIST_NODE:
case INS_NODE:
case WHATSIT_NODE:
case MARK_NODE:
case ADJUST_NODE:
case UNSET_NODE:
    print("[]");
    break;

case RULE_NODE:
    print_char('|');
    break;

case GLUE_NODE:
    if (glue_ptr(p) != ZERO_GLUE) {
        print_char(' ');
    }
    break;

case MATH_NODE:
    print_char('$');
    break;

case LIGATURE_NODE:
    short_display(lig_ptr(p));
    break;

case DISC_NODE:
    short_display(pre_break(p));
    short_display(post_break(p));
    n = replace_count(p);
    while (n > 0) {
        if (link(p) != null) {
            p = link(p);
        }
        decr(n);
    }
    break;

default:
    do_nothing;
}
```
