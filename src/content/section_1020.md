# Section 1020

We will set *best_ins_ptr* &larr; *null* and package the box corresponding to insertion node&nbsp;*r*, just after making the final insertion into that box.
If this final insertion is *'SPLIT_UP'*, the remainder after splitting and pruning (if any) will be carried over to the next page.

```c << Either insert the material specified by node |p| into the appropriate box, or hold it for the next page; also delete node |p| from the current page >>=
r = link(PAGE_INS_HEAD);
while (subtype(r) != subtype(p)) {
    r = link(r);
}
if (best_ins_ptr(r) == null) {
    wait = true;
}
else {
    wait = false;
    s = last_ins_ptr(r);
    link(s) = ins_ptr(p);
    if (best_ins_ptr(r) == p) {
        // << Wrap up the box specified by node |r|, splitting node |p| if called for; set |wait = true| if node |p| holds a remainder after splitting >>
    }
    else {
        while (link(s) != null) {
            s = link(s);
        }
        last_ins_ptr(r) = s;
    }
}
// << Either append the insertion node |p| after node |q|, and remove it from the current page, or delete |node(p)| >>
```
