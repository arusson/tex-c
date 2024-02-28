# Section 915

The new hyphen might combine with the previous character via ligature or kern.
At this point we have *l − 1* $\leq$ *i* $<$ *j* and *i* $<$ *hn*.

```c << Put the characters |hu[l..i]| and a hyphen into |pre_break(r)| >>=
minor_tail = null;
pre_break(r) = null;
hyf_node = new_character(hf, hyf_char);
if (hyf_node != null) {
    incr(i);
    c = hu[i];
    hu[i] = hyf_char;
    free_avail(hyf_node);
}
while (l <= i) {
    l = reconstitute(l, i, font_bchar[hf], NON_CHAR) + 1;
    if (link(HOLD_HEAD) > null) {
        if (minor_tail == null) {
            pre_break(r) = link(HOLD_HEAD);
        }
        else {
            link(minor_tail) = link(HOLD_HEAD);
        }
        minor_tail = link(HOLD_HEAD);
        while (link(minor_tail) > null) {
            minor_tail = link(minor_tail);
        }
    }
}
if (hyf_node != null) {
    hu[i] = c; // restore the character in the hyphen position
    l = i;
    decr(i);
}
```
