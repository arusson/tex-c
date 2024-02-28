# Section 1191

```c math/math_lists.c
void math_left_right() {
    small_number t; // |LEFT_NOAD| or |RIGHT_NOAD|
    pointer p;      // new noad
    t = cur_chr;
    if (t == RIGHT_NOAD && cur_group != MATH_LEFT_GROUP) {
        // << Try to recover from mismatched \right >>
    }
    else {
        p = new_noad();
        type(p) = t;
        scan_delimiter(delimiter(p), false);
        if (t == LEFT_NOAD) {
            push_math(MATH_LEFT_GROUP);
            link(head) = p;
            tail = p;
        }
        else {
            p = fin_mlist(p);
            unsave(); // end of |MATH_LEFT_GROUP|
            tail_append(new_noad());
            type(tail) = INNER_NOAD;
            math_type(nucleus(tail)) = SUB_MLIST;
            info(nucleus(tail)) = p;
        }
    }
}
```
