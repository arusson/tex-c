# Section 1080

Note that the condition *¬is_char_node(tail)* implies that *head* $\ne$ *tail*, since *head* is a one-word node.

```c << If the current list ends with a box node, delete it from the list and make |cur_box| point to it; otherwise set |cur_box = null| >>=
cur_box = null;
if (abs(mode) == MMODE) {
    you_cant();
    help1("Sorry; this \\lastbox will be void.");
    error();
}
else if (mode == VMODE && head == tail) {
    you_cant();
    help2("Sorry...I usually can't take things from the current page.")
        ("This \\lastbox will therefore be void.");
    error();
}
else if (!is_char_node(tail)
    && (type(tail) == HLIST_NODE || type(tail) == VLIST_NODE))
{
    // << Remove the last box, unless it's part of a discretionary >>
}
```
