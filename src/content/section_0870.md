# Section 870

```c << Add the width of node |s| to |disc_width| >>=
if (is_char_node(s)) {
    f = font(s);
    disc_width += char_width(f, char_info(f, character(s)));
}
else {
    switch (type(s)) {
    case LIGATURE_NODE:
        f = font(lig_char(s));
        disc_width += char_width(f, char_info(f, character(lig_char(s)))); 
        break;
    
    case HLIST_NODE:
    case VLIST_NODE:
    case RULE_NODE:
    case KERN_NODE:
        disc_width += width(s);
        break;
    
    default:
        confusion("disc3");
    }
}
```
