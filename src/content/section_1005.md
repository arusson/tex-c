# Section 1005

```c << Check if node |p| is a new champion breakpoint; then if it is time for a page break, prepare for output, and either fire up the user's output routine and |return| or ship out the page and |goto done| >>=
if (pi < INF_PENALTY) {
    // << Compute the badness, |b|, of the current page, using |AWFUL_BAD| if the box is too full >>
    if (b < AWFUL_BAD) {
        if (pi <= EJECT_PENALTY) {
            c = pi;
        }
        else if (b < INF_BAD) {
            c = b + pi + insert_penalties;
        }
        else {
            c = DEPLORABLE;
        }
    }
    else {
        c = b;
    }
    if (insert_penalties >= 10000) {
        c = AWFUL_BAD;
    }

#ifdef STAT
    if (tracing_pages > 0) {
        // << Display the page break cost >>
    }
#endif

    if (c <= least_page_cost) {
        best_page_break = p;
        best_size = page_goal;
        least_page_cost = c;
        r = link(PAGE_INS_HEAD);
        while (r != PAGE_INS_HEAD) {
            best_ins_ptr(r) = last_ins_ptr(r);
            r = link(r);
        }
    }
    if (c == AWFUL_BAD || pi <= EJECT_PENALTY) {
        fire_up(p); // output the current page at the best place
        if (output_active) {
            return; // user's output routine will act
        }
        goto done; // the page has been shipped out by default output routine
    }
}
```
