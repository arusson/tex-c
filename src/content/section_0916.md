# Section 916

The synchronization algorithm begins with *l = i + 1* $\leq$ *j*.

```c << Put the characters |hu[i + 1..]| into |post_break(r)|, appending to this list and to |major_tail| until synchronization has been achieved >>=
minor_tail = null;
post_break(r) = null;
c_loc = 0;
if (bchar_label[hf] != NON_ADDRESS) {
    // put left boundary at beginning of new line
    decr(l);
    c = hu[l];
    c_loc = l;
    hu[l] = 256;
}
while (l < j) {
    do {
        l = reconstitute(l, hn, bchar, NON_CHAR) + 1;
        if (c_loc > 0) {
            hu[c_loc] = c;
            c_loc = 0;
        }
        if (link(HOLD_HEAD) > null) {
            if (minor_tail == null) {
                post_break(r) = link(HOLD_HEAD);
            }
            else {
                link(minor_tail) = link(HOLD_HEAD);
            }
            minor_tail = link(HOLD_HEAD);
            while (link(minor_tail) > null) {
                minor_tail = link(minor_tail);
            }
        }
    } while (l < j);
    while (l > j) {
        // << Append characters of |hu[j..]| to |major_tail|, advancing |j| >>
    }
}
```

