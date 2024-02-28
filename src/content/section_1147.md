# Section 1147

```c << Let |d| be the natural width of node |p|; if the node is "visible," |goto found|; if the node is glue that stretches or shrinks, set |v = MAX_DIMEN| >>=
reswitch:
if (is_char_node(p)) {
    f = font(p);
    d = char_width(f, char_info(f, character(p)));
    goto found;
}

switch (type(p)) {
case HLIST_NODE:
case VLIST_NODE:
case RULE_NODE:
    d = width(p);
    goto found;

case LIGATURE_NODE:
    // << Make node |p| look like a |CHAR_NODE| and |goto reswitch| >>

case KERN_NODE:
case MATH_NODE:
    d = width(p);
    break;

case GLUE_NODE:
    // << Let |d| be the natural width of this glue; if stretching or shrinking, set |v = MAX_DIMEN|; |goto found| in the case of leaders >>
    break;

case WHATSIT_NODE:
    // << Let |d| be the width of the whatsit |p| >>
    break;

default:
    d = 0;
}
```
