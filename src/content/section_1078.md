# Section 1078

```c << Append a new leader node that uses |cur_box| >>=
// << Get the next non-blank non-relax non-call token >>
if ((cur_cmd == HSKIP && abs(mode) != VMODE)
    || (cur_cmd == VSKIP && abs(mode) == VMODE))
{
    append_glue();
    subtype(tail) = box_context - (LEADER_FLAG - A_LEADERS);
    leader_ptr(tail) = cur_box;
}
else {
    print_err("Leaders not followed by proper glue");
    help3("You should say `\\leaders <box or rule><hskip or vskip>'.")
        ("I found the <box or rule>, but there's no suitable")
        ("<hskip or vskip>, so I'm ignoring these leaders.");
    back_error();
    flush_node_list(cur_box);
}
```
