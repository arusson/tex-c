# Section 982

An array *page_so_far* records the heights and depths of everything on the current page.
This array contains six *scaled* numbers, like the similar arrays already considered in *line_break* and *vert_break*; and it also contains *page_goal* and *page_depth*, since these values are all accessible to the user via *set_page_dimen* commands.
The value of *page_so_far[1]* is also called *page_total*.
The stretch and shrink components of the `\skip` corrections for each insertion are included in *page_so_far*, but the natural space components of these corrections are not, since they have been subtracted from *page_goal*.

The variable *page_depth* records the depth of the current page; it has been adjusted so that it is at most *page_max_depth*.
The variable *last_glue* points to the glue specification of the most recent node
contributed from the contribution list, if this was a glue node; otherwise *last_glue = MAX_HALFWORD*.
(If the contribution list is nonempty, however, the value of *last_glue* is not necessarily accurate.)
The variables *last_penalty* and *last_kern* are similar.
And finally, *insert_penalties* holds the sum of the penalties associated with
all split and floating insertions.

```c include/builder.h
#define page_goal   page_so_far[0] // desired height of information on page being built
#define page_total  page_so_far[1] // height of the current page
#define page_shrink page_so_far[6] // shrinkability of the current page
#define page_depth  page_so_far[7] // depth of the current page
```

```c << Global variables >>+=
scaled  page_so_far[8];   // height and glue of the current page
pointer last_glue;        // used to implement \lastskip
int     last_penalty;     // used to implement \lastpenalty
scaled  last_kern;        // used to implement \lastkern
int     insert_penalties; // sum of the penalties for insertions that were held over
```
