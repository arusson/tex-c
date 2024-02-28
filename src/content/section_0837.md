# Section 837

When we insert a new active node for a break at *cur_p*, suppose this new node is to be placed just before active node $a$;
then we essentially want to insert '$\delta$, *cur_p* $\delta'$' before $a$, where $\delta = \alpha(a) - \alpha($*cur_p*$)$ and $\delta' = \alpha($*cur_p*$) - \alpha(a)$ in the notation explained above.
The *cur_active_width* array now holds $\gamma + \beta($*cur_p*$) - \alpha(a)$;
so $\delta$ can be obtained by subtracting *cur_active_width* from the quantity $\gamma + \beta($*cur_p*$) - \alpha($*cur_p*$)$.
The latter quantity can be regarded as the length of a line "from *cur_p* to *cur_p*";
we call it the *break_width* at *cur_p*.

The *break_width* is usually negative, since it consists of the background (which is normally zero) minus the width of nodes following&nbsp;*cur_p* that are eliminated after a break.
If, for example, node *cur_p* is a glue node, the width of this glue is subtracted from the background; and we also look ahead to eliminate all subsequent glue and penalty and kern and math nodes, subtracting their widths as well.

Kern nodes do not disappear at a line break unless they are *EXPLICIT*.

```c include/breaker.h
#define set_break_width_to_background(X) break_width[(X)] = background[(X)]
```

```c << Compute the values of |break_width| >>=
no_break_yet = false;
do_all_six(set_break_width_to_background);
s = cur_p;
if (break_type > UNHYPHENATED && cur_p != null) {
    // << Compute the discretionary |break_width| values >>
}
while (s != null) {
    if (is_char_node(s)) {
        goto done;
    }
    switch (type(s)) {
    case GLUE_NODE:
        // << Subtract glue from |break_width| >>
        break;
    
    case PENALTY_NODE:
        do_nothing;
        break;
    
    case MATH_NODE:
        break_width[1] -= width(s);
        break;
    
    case KERN_NODE:
        if (subtype(s) != EXPLICIT) {
            goto done;
        }
        else {
            break_width[1] -= width(s);
        }
        break;
    
    default:
        goto done;
    }
    s = link(s);
}
done:
```
