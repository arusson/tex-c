# Section 979

It's possible that the box begins with a penalty node that is the "best" break, so we must be careful to handle this special case correctly.

```c << Look at all the marks in nodes before the break, and set the final link to |null| at the break >>=
p = list_ptr(v);
if (p == q) {
    list_ptr(v) = null;
}
else {
    while(true) {
        if (type(p) == MARK_NODE) {
            if (split_first_mark == null) {
                split_first_mark = mark_ptr(p);
                split_bot_mark = split_first_mark;
                token_ref_count(split_first_mark) += 2;
            }
            else {
                delete_token_ref(split_bot_mark);
                split_bot_mark = mark_ptr(p);
                add_token_ref(split_bot_mark);
            }
        }
        if (link(p) == q) {
            link(p) = null;
            break; // goto done
        }
        p = link(p);
    }
}
// done:
```
