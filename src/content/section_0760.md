# Section 760

We have now tied up all the loose ends of the first pass of *mlist_to_hlist*.
The second pass simply goes through and hooks everything together with the proper glue and penalties.
It also handles the *LEFT_NOAD* and *RIGHT_NOAD* that might be present, since *max_h* and *max_d* are now known.
Variable *p* points to a node at the current end of the final hlist.

```c << Make a second pass over the mlist, removing all noads and inserting the proper spacing and penalties >>=
p = TEMP_HEAD;
link(p) = null;
q = mlist;
r_type = 0;
cur_style = style;
// << Set up the values of |cur_size| and |cur_mu|, based on |cur_style| >>
while (q != null) {
    // << If node |q| is a style node, change the style and |goto delete_q|; otherwise if it is not a noad, put it into the hlist, advance |q|, and |goto done|; otherwise set |s| to the size of noad |q|, set |t| to the associated type (|ORD_NOAD .. INNER_NOAD|), and set |pen| to the associated penalty >>

    // << Append inter-element spacing based on |r_type| and |t| >>

    // << Append any |new_hlist| entries for |q|, and any appropriate penalties >>
    r_type = t;
delete_q:
    r = q;
    q = link(q);
    free_node(r, s);
// done: (equivalent to continue the loop)
}
```
