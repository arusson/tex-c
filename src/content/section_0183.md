# Section 183

```c << Display node |p| >>=
if (is_char_node(p)) {
    print_font_and_char(p);
}
else {
    switch(type(p)) {
    case HLIST_NODE:
    case VLIST_NODE:
    case UNSET_NODE:
        // << Display box |p| >>
        break;
    
    case RULE_NODE:
        // << Display rule |p| >>
        break;
    
    case INS_NODE:
        // << Display insertion |p| >>
        break;
    
    case WHATSIT_NODE:
        // << Display the whatsit node |p| >>
        break;
    
    case GLUE_NODE:
        // << Display glue |p| >>
        break;
    
    case KERN_NODE:
        // << Display kern |p| >>
        break;
    
    case MATH_NODE:
        // << Display math node |p| >>
        break;
    
    case LIGATURE_NODE:
        // << Display ligature |p| >>
        break;
    
    case PENALTY_NODE:
        // << Display penalty |p| >>
        break;
    
    case DISC_NODE:
        // << Display discretionary |p| >>
        break;
    
    case MARK_NODE:
        // << Display mark |p| >>
        break;
    
    case ADJUST_NODE:
        // << Display adjustment |p| >>
        break;
    
    // << Cases of |show_node_list| that arise in mlists only >>

    default:
        print("Unknown node type!");
    }
}
```
