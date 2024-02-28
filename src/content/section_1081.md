# Section 1081

```c << Remove the last box, unless it's part of a discretionary >>=
q = head;
do {
    p = q;
    if (!is_char_node(q) && type(q) == DISC_NODE) {
        for(m = 1; m <= replace_count(q); m++) {
            p = link(p);
        }
        if (p == tail) {
            goto done;
        }
    }
    q = link(p);
} while (q != tail);
cur_box = tail;
shift_amount(cur_box) = 0;
tail = p;
link(p) = null;
done:
```
