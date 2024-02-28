# Section 1184

At the end of a math formula or subformula, the *fin_mlist* routine is called upon to return a pointer to the newly completed mlist, and to pop the nest back to the enclosing semantic level.
The parameter to *fin_mlist*, if not null, points to a *RIGHT_NOAD* that ends the
current mlist; this *RIGHT_NOAD* has not yet been appended.

```c << Declare the function called |fin_mlist| >>=
pointer fin_mlist(pointer p) {
    pointer q; // the mlist to return
    if (incompleat_noad != null) {
        // << Compleat the incompleat noad >>
    }
    else {
        link(tail) = p;
        q = link(head);
    }
    pop_nest();
    return q;
}
```
