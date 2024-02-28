# Section 866

Here is the main switch in the *line_break* routine, where legal breaks are determined.
As we move through the hlist, we need to keep the *active_width* array up to date, so that the badness of individual lines is readily calculated by *try_break*.
It is convenient to use the short name *act_width* for the component of active width that represents real width as opposed to glue.

```c include/breaker.h
#define act_width active_width[1] // length from first active node to current node
#define kern_break                             \
    do {                                       \
        if (!is_char_node(link(cur_p))         \
            && auto_breaking                   \
            && type(link(cur_p)) == GLUE_NODE) \
        {                                      \
            try_break(0, UNHYPHENATED);        \
        }                                      \
        act_width += width(cur_p);             \
    } while (0)
```

```c << Call |try_break| if |cur_p| is a legal breakpoint; on the second pass, also try to hyphenate the next word, if |cur_p| is a glue node; then advance |cur_p| to the next node of the paragraph that could possibly be a legal breakpoint >>=
if (is_char_node(cur_p)) {
    // << Advance |cur_p| to the node following the present string of characters >>
}
switch (type(cur_p)) {
case HLIST_NODE:
case VLIST_NODE:
case RULE_NODE:
    act_width += width(cur_p);
    break;

case WHATSIT_NODE:
    // << Advance past a whatsit node in the |line_break| loop >>
    break;

case GLUE_NODE:
    // << If node |cur_p| is a legal breakpoint, call |try_break|; then update the active widths by including the glue in |glue_ptr(cur_p)| >>
    if (second_pass && auto_breaking) {
        // << Try to hyphenate the following word >>
    }
    break;

case KERN_NODE:
    if (subtype(cur_p) == EXPLICIT) {
        kern_break;
    }
    else {
        act_width += width(cur_p);
    }
    break;

case LIGATURE_NODE:
    f = font(lig_char(cur_p));
    act_width += char_width(f, char_info(f, character(lig_char(cur_p))));
    break;

case DISC_NODE:
    // << Try to break after a discretionary fragment, then |goto done5| >>

case MATH_NODE:
    auto_breaking = (subtype(cur_p) == AFTER);
    kern_break;
    break;

case PENALTY_NODE:
    try_break(penalty(cur_p), UNHYPHENATED);
    break;

case MARK_NODE:
case INS_NODE:
case ADJUST_NODE:
    do_nothing;
    break;

default:
    confusion("paragraph");
}
prev_p = cur_p;
cur_p = link(cur_p);
done5:
```
