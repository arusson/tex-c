# Section 727

We use the fact that no character nodes appear in an mlist, hence the field *type(q)* is always present.

```c << Process node-or-noad |q| as much as possible in preparation for the second pass of |mlist_to_hlist|, then move to the next item in the mlist >>=
// << Do first-pass processing based on |type(q)|; |goto done_with_noad| if a noad has been fully processed, |goto check_dimensions| if it has been translated into |new_hlist(q)|, or |goto done_with_node| if a node has been fully processed >>

check_dimensions:
z = hpack(new_hlist(q), NATURAL);
if (height(z) > max_h) {
    max_h = height(z);
}
if (depth(z) > max_d) {
    max_d = depth(z);
}
free_node(z, BOX_NODE_SIZE);

done_with_noad:
r = q;
r_type = type(r);

done_with_node:
q = link(q);
```
