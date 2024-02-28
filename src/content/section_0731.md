# Section 731

```c include/texmath.h
#define choose_mlist(X) p = X(q); X(q) = null
```

```c << Change this node to a style node followed by the correct choice, then |goto done_with_node| >>=
switch (cur_style / 2) {
case 0:
    // |DISPLAY_STYLE = 0|
    choose_mlist(display_mlist);
    break;

case 1:
    // |TEXT_STYLE = 2|
    choose_mlist(text_mlist);
    break;

case 2:
    // |SCRIPT_STYLE = 4|
    choose_mlist(script_mlist);
    break;

default:
    // case 3:
    // |SCRIPT_SCRIPT_STYLE = 6|
    choose_mlist(script_script_mlist);
} // there are no other cases
flush_node_list(display_mlist(q));
flush_node_list(text_mlist(q));
flush_node_list(script_mlist(q));
flush_node_list(script_script_mlist(q));
type(q) = STYLE_NODE;
subtype(q) = cur_style;
width(q) = 0;
depth(q) = 0;
if (p != null){
    z = link(q);
    link(q) = p;
    while (link(p) != null) {
        p = link(p);
    }
    link(p) = z;
}
goto done_with_node;
```
