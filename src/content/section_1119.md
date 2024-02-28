# Section 1119

```c builder/boxes_and_lists.c
void build_discretionary() {
    pointer p, q; // for link manipulation
    int n;        // length of discretionary list
    unsave();
    // << Prune the current list, if necessary, until it contains only |CHAR_NODE|, |KERN_NODE|, |HLIST_NODE|, |VLIST_NODE|, |RULE_NODE|, and |LIGATURE_NODE| items; set |n| to the length of the list, and set |q| to the list's tail >>
    p = link(head);
    pop_nest();
    switch (saved(-1)) {
    case 0:
        pre_break(tail) = p;
        break;
    
    case 1:
        post_break(tail) = p;
        break;
    
    case 2:
        // << Attach list |p| to the current list, and record its length; then finish up and |return| >>
    } // there are no other cases
    incr(saved(-1));
    new_save_level(DISC_GROUP);
    scan_left_brace();
    push_nest();
    mode = -HMODE;
    space_factor = 1000;
}
```
