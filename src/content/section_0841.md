# Section 841

Replacement texts and discretionary texts are supposed to contain only character nodes, kern nodes, ligature nodes, and box or rule nodes.

```c << Subtract the width of node |v| from |break_width| >>=
if (is_char_node(v)) {
    f = font(v);
    break_width[1] -= char_width(f, char_info(f, character(v)));
}
else {
    switch (type(v)) {
    case LIGATURE_NODE:
        f = font(lig_char(v));
        break_width[1] -= char_width(f, char_info(f, character(lig_char(v))));
        break;
    
    case HLIST_NODE:
    case VLIST_NODE:
    case RULE_NODE:
    case KERN_NODE:
        break_width[1] -= width(v);
        break;
    
    default:
        confusion("disc1");
    }
}
```
