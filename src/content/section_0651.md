# Section 651

```c << Examine node |p| in the hlist, taking account of its effect on the dimensions of the new box, or moving it to the adjustment list; then advance |p| to the next node >>=
reswitch:
while (is_char_node(p)) {
    // << Incorporate character dimensions into the dimensions of the hbox that will contain it, then move to the next node >>
}
if (p != null) {
    switch (type(p)) {
    case HLIST_NODE:
    case VLIST_NODE:
    case RULE_NODE:
    case UNSET_NODE:
        // << Incorporate box dimensions into the dimensions of the hbox that will contain it >>
        break;
    
    case INS_NODE:
    case MARK_NODE:
    case ADJUST_NODE:
        if (adjust_tail != null) {
            // << Transfer node |p| to the adjustment list >>
        }
        break;
    
    case WHATSIT_NODE:
        // << Incorporate a whatsit node into an hbox >>
        break;
    
    case GLUE_NODE:
        // << Incorporate glue into the horizontal totals >>
        break;
    
    case KERN_NODE:
    case MATH_NODE:
        x += width(p);
        break;
    
    case LIGATURE_NODE:
        // << Make node |p| look like a |CHAR_NODE| and |goto reswitch| >>
    
    default:
        do_nothing;
    }
    p = link(p);
}
```
