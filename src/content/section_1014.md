# Section 1014

As the page is finally being prepared for output, pointer *p* runs through the vlist, with *prev_p* trailing behind;
pointer *q* is the tail of a list of insertions that are being held over for a subsequent page.

```c << Put the optimal current page into box 255, update |first_mark| and |bot_mark|, append insertions to their boxes, and put the remaining nodes back on the contribution list >>=
if (c == best_page_break) {
    best_page_break = null; // |c| not yet linked in
}

// << Ensure that box 255 is empty before output >>

insert_penalties = 0; // this will count the number of insertions held over
save_split_top_skip = split_top_skip;
if (holding_inserts <= 0) {
    // << Prepare all the boxes involved in insertions to act as queues >>
}
q = HOLD_HEAD;
link(q) = null;
prev_p = PAGE_HEAD;
p = link(prev_p);
while (p != best_page_break) {
    if (type(p) == INS_NODE) {
        if (holding_inserts <= 0) {
            // << Either insert the material specified by node |p| into the appropriate box, or hold it for the next page; also delete node |p| from the current page >>
        }
    }
    else if (type(p) == MARK_NODE) {
        // << Update the values of |first_mark| and |bot_mark| >>
    }
    prev_p = p;
    p = link(prev_p);
}
split_top_skip = save_split_top_skip;

// << Break the current page at node |p|, put it in box 255, and put the remaining nodes on the contribution list >>

// << Delete the page-insertion nodes >>
```
