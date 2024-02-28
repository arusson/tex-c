# Section 977

Now we are ready to consider *vsplit* itself.
Most of its work is accomplished by the two subroutines that we have just considered.

Given the number of a vlist box *n*, and given a desired page height *h*, the *vsplit* function finds the best initial segment of the vlist and returns a box for a page of height&nbsp;*h*.
The remainder of the vlist, if any, replaces the original box, after removing glue and penalties and adjusting for *split_top_skip*.
Mark nodes in the split-off box are used to set the values of *split_first_mark* and *split_bot_mark*; we use the fact that *split_first_mark = null* if and only if *split_bot_mark = null*.

The original box becomes "void" if and only if it has been entirely extracted.
The extracted box is "void" if and only if the original box was void (or if it was, erroneously, an hlist box).

```c breaker/page_break.c
// extracts a page of height |h| from box |n|
pointer vsplit(eight_bits n, scaled h) {
    pointer v; // the box to be split
    pointer p; // runs through the vlist
    pointer q; // points to where the break occurs
    v = box(n);
    if (split_first_mark != null) {
        delete_token_ref(split_first_mark);
        split_first_mark = null;
        delete_token_ref(split_bot_mark);
        split_bot_mark = null;
    }
    // << Dispense with trivial cases of void or bad boxes >>
    q = vert_break(list_ptr(v), h, split_max_depth);
    // << Look at all the marks in nodes before the break, and set the final link to |null| at the break >>
    q = prune_page_top(q);
    p = list_ptr(v);
    free_node(v, BOX_NODE_SIZE);
    if (q == null) {
        box(n) = null; // the |eq_level| of the box stays the same
    }
    else {
        box(n) = vpack(q, NATURAL);
    }
    return vpackage(p, h, EXACTLY, split_max_depth);
}
```
