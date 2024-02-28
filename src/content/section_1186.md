# Section 1186

Now at last we're ready to see what happens when a right brace occurs
in a math formula.
Two special cases are simplified here: Braces are effectively
removed when they surround a single Ord without sub/superscripts, or when they
surround an accent that is the nucleus of an Ord atom.

```c << Cases of |handle_right_brace| where a |RIGHT_BRACE| triggers a delayed action >>+=
case MATH_GROUP:
    unsave();
    decr(save_ptr);
    math_type(saved(0)) = SUB_MLIST;
    p = fin_mlist(null);
    info(saved(0)) = p;
    if (p != null && link(p) == null) {
        if (type(p) == ORD_NOAD) {
            if (math_type(subscr(p)) == EMPTY && math_type(supscr(p)) == EMPTY) {
                mem[saved(0)] = mem[nucleus(p)];
                free_node(p, NOAD_SIZE);
            }
        }
        else if (type(p) == ACCENT_NOAD
            && saved(0) == nucleus(tail)
            && type(tail) == ORD_NOAD)
        {
            // << Replace the tail of the list by |p| >>
        }
    }
    break;
```
