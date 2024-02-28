# Section 980: The page builder

When $\TeX$ appends new material to its main vlist in vertical mode, it uses a method something like *vsplit* to decide where a page ends, except that the calculations are done "on line" as new items come in.
The main complication in this process is that insertions must be put into their boxes and removed from the vlist, in a more-or-less optimum manner.

We shall use the term "current page" for that part of the main vlist that is being considered as a candidate for being broken off and sent to the user's output routine.
The current page starts at *link(PAGE_HEAD)*, and it ends at *page_tail*.
We have *PAGE_HEAD = page_tail* if this list is empty.

Utter chaos would reign if the user kept changing page specifications while a page is being constructed, so the page builder keeps the pertinent specifications frozen as soon as the page receives its first box or insertion.
The global variable *page_contents* is *EMPTY* when the current page contains only mark nodes and content-less whatsit nodes;
it is *inserts_only* if the page contains only insertion nodes in addition to
marks and whatsits.
Glue nodes, kern nodes, and penalty nodes are discarded until a box or rule node appears, at which time *page_contents* changes to *BOX_THERE*.
As soon as *page_contents* becomes non-*EMPTY*, the current *vsize* and *max_depth* are squirreled away into *page_goal* and *page_max_depth*; the latter values will be used until the page has been forwarded to the user's output routine.
The `\topskip` adjustment is made when *page_contents* changes to *BOX_THERE*.

Although *page_goal* starts out equal to *vsize*, it is decreased by the scaled natural height-plus-depth of the insertions considered so far, and by the `\skip` corrections for those insertions.
Therefore it represents the size into which the non - inserted material should fit, assuming that all insertions in the current page have been made.

The global variables *best_page_break* and *least_page_cost* correspond respectively to the local variables *best_place* and *least_cost* in the *vert_break* routine that we have already studied; i.e., they record the location and value of the best place currently known for breaking the current page.
The value of *page_goal* at the time of the best break is stored in *best_size*.

```c include/constants.h
#define INSERTS_ONLY 1 // |page_contents| when an insert node has been contributed, but no boxes
#define BOX_THERE    2 // |page_contents| when a box or rule has been contributed
```

```c << Global variables >>+=
pointer page_tail;       // the final node on the current page
int     page_contents;   // what is on the current page so far?
scaled  page_max_depth;  // maximum box depth on page being built
pointer best_page_break; // break here to get the best page known so far
int     least_page_cost; // the score for this currently best page
scaled  best_size;       // its |page_goal|
```
