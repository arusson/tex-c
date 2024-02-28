# Section 819

An active node for a given breakpoint contains six fields:

- *link* points to the next node in the list of active nodes;
  the last active node has *link = LAST_ACTIVE*.
- *break_node* points to the passive node associated
  with this breakpoint.
- *line_number* is the number of the line that follows
  this breakpoint.
- *fitness* is the fitness classification of the line ending
  at this breakpoint.
- *type* is either *HYPHENATED* or *UNHYPHENATED*, depending on whether
  this breakpoint is a *DISC_NODE*.
- *total_demerits* is the minimum possible sum of demerits over all
  lines leading from the beginning of the paragraph to this breakpoint.

The value of *link(ACTIVE)* points to the first active node on a linked list of all currently active nodes.
This list is in order by *line_number*, except that nodes with *line_number* $>$ *easy_line* may be in any order relative to each other.

```c include/constants.h
#define ACTIVE_NODE_SIZE 3      // number of words in active nodes
#define UNHYPHENATED     0      // the |type| of a normal active break node
#define HYPHENATED       1      // the |type| of an active node that breaks at a |DISC_NODE|
#define LAST_ACTIVE      ACTIVE // the active list ends where it begins
```

```c include/breaker.h
// << Start file |breaker.h| >>

#define fitness           subtype              // |VERY_LOOSE_FIT .. TIGHT_FIT| on final line for this break
#define break_node        rlink                // pointer to the corresponding passive node
#define line_number       llink                // line that begins at this breakpoint
#define total_demerits(X) mem[(X) + 2].integer // the quantity that TeX minimizes
```
