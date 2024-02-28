# Section 719: Typesetting math formulas

$\TeX$'s most important routine for dealing with formulas is called *mlist_to_hlist*.
After a formula has been scanned and represented as an mlist, this routine converts it to an hlist that can be placed into a box or incorporated into the text of a paragraph.
There are three implicit parameters, passed in global variables: *cur_mlist* points to the first node or noad in the given mlist (and it might be *null*); *cur_style* is a style code; and *mlist_penalties* is *true* if penalty nodes for potential line breaks are to be inserted into the resulting hlist.
After *mlist_to_hlist* has acted, *link(TEMP_HEAD)* points to the translated hlist.

Since mlists can be inside mlists, the procedure is recursive.
And since this is not part of $\TeX$'s inner loop, the program has been written in a manner that stresses compactness over efficiency.

```c << Global variables >>+=
pointer      cur_mlist; // beginning of mlist to be translated
small_number cur_style; // style code at current place in the list
small_number cur_size;  // size code corresponding to |cur_style|
scaled       cur_mu;    // the math unit width corresponding to |cur_size|
bool mlist_penalties;   // should |mlist_to_hlist| insert penalties?
```
