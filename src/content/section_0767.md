# Section 767

We insert a penalty node after the hlist entries of noad *q* if *pen* is not an "infinite" penalty, and if the node immediately following *q* is not a penalty node or a *REL_NOAD* or absent entirely.

```c << Append any |new_hlist| entries for |q|, and any appropriate penalties >>=
if (new_hlist(q) != null) {
    link(p) = new_hlist(q);
    do {
        p = link(p);
    } while (link(p) != null);
}
if (penalties
    && link(q) != null
    && pen < INF_PENALTY)
{
    r_type = type(link(q));
    if (r_type != PENALTY_NODE && r_type != REL_NOAD) {
        z = new_penalty(pen);
        link(p) = z;
        p = z;
    }
}
```
