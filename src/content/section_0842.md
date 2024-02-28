# Section 842

```c << Add the width of node |s| to |break_width| >>=
if (is_char_node(s)) {
    f = font(s);
    break_width[1] += char_width(f, char_info(f, character(s)));
}
else {
    switch (type(s)) {
    case LIGATURE_NODE:
        f = font(lig_char(s));
        break_width[1] += char_width(f, char_info(f, character(lig_char(s))));
        break;

    case HLIST_NODE:
    case VLIST_NODE:
    case RULE_NODE:
    case KERN_NODE:
        break_width[1] += width(s);
        break;
    
    default:
        confusion("disc2");
    }
}
```
