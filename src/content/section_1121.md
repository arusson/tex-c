# Section 1121

During this loop, *p = link(q)* and there are *n* items preceding *p*.

```c << Prune the current list, if necessary, until it contains only |CHAR_NODE|, |KERN_NODE|, |HLIST_NODE|, |VLIST_NODE|, |RULE_NODE|, and |LIGATURE_NODE| items; set |n| to the length of the list, and set |q| to the list's tail >>
q = head;
p = link(q);
n = 0;
while (p != null) {
    if (!is_char_node(p)
        && type(p) > RULE_NODE
        && type(p) != KERN_NODE
        && type(p) != LIGATURE_NODE)
    {
        print_err("Improper discretionary list");
        help1("Discretionary lists must contain only boxes and kerns.");
        error();
        begin_diagnostic();
        print_nl("The following discretionary sublist has been deleted:");
        show_box(p);
        end_diagnostic(true);
        flush_node_list(p);
        link(q) = null;
        break; // goto done
    }
    q = p;
    p = link(q);
    incr(n);
}
// done:
```
