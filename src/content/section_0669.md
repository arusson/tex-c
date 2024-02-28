# Section 669

```c << Examine node |p| in the vlist, taking account of its effect on the dimensions of the new box; then advance |p| to the next node >>=
if (is_char_node(p)) {
    confusion("vpack");
}
else {
    switch (type(p)) {
    case HLIST_NODE:
    case VLIST_NODE:
    case RULE_NODE:
    case UNSET_NODE:
        // << Incorporate box dimensions into the dimensions of the vbox that will contain it >>
        break;
    
    case WHATSIT_NODE:
        // << Incorporate a whatsit node into a vbox >>
        break;
    
    case GLUE_NODE:
        // << Incorporate glue into the vertical totals >>
        break;
    
    case KERN_NODE:
        x += d + width(p);
        d = 0;
        break;
    
    default:
        do_nothing;
    }
}
p = link(p);
```
