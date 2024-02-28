# Section 871

```c << Add the width of node |s| to |act_width| >>=
if (is_char_node(s)) {
    f = font(s);
    act_width += char_width(f, char_info(f, character(s)));
}
else {
    switch (type(s)) {
    case LIGATURE_NODE:
        f = font(lig_char(s));
        act_width += char_width(f, char_info(f, character(lig_char(s))));
        break;
    
    case HLIST_NODE:
    case VLIST_NODE:
    case RULE_NODE:
    case KERN_NODE:
        act_width += width(s);
        break;
    
    default:
        confusion("disc4");
    }
}
```
