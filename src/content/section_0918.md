# Section 918

Ligature insertion can cause a word to grow exponentially in size.
Therefore we must test the size of *r_count* here, even though the hyphenated text was at most 63 characters long.

```c << Move pointer |s| to the end of the current list, and set |replace_count(r)| appropriately >>=
if (r_count > 127) {
    // we have to forget the discretionary hyphen
    link(s) = link(r);
    link(r) = null;
    flush_node_list(r);
}
else {
    link(s) = r;
    replace_count(r) = r_count;
}
s = major_tail;
```
