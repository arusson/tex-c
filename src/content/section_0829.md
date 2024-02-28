# Section 829

The heart of the line-breaking procedure is *'try_break'*, a subroutine that tests if the current breakpoint *cur_p* is feasible, by running through the active list to see what lines of text can be made from active nodes to&nbsp;*cur_p*.
If feasible breaks are possible, new break nodes are created.
If *cur_p* is too far from an active node, that node is deactivated.

The parameter *pi* to *try_break* is the penalty associated with a break at *cur_p*; we have *pi = EJECT_PENALTY* if the break is forced, and *pi = INF_PENALTY* if the break is illegal.

The other parameter, *break_type*, is set to *HYPHENATED* or *UNHYPHENATED*, depending on whether or not the current break is at a *DISC_NODE*.
The end of a paragraph is also regarded as *'HYPHENATED'*; this case is distinguishable by the condition *cur_p = null*.

```c include/breaker.h
#define copy_to_cur_active(X) cur_active_width[(X)] = active_width[(X)]
```

```c << Declare subprocedures for |line_break| >>+=
void try_break(int pi, small_number break_type) {
    pointer r;      // runs through the active list
    pointer prev_r; // stays a step behind |r|
    halfword old_l; // maximum line number in current equivalence class of lines
    bool no_break_yet; // have we found a feasible break at |cur_p|?
    // << Other local variables for |try_break| >>
    
    // << Make sure that |pi| is in the proper range >>
    no_break_yet = true;
    prev_r = ACTIVE;
    old_l = 0;
    do_all_six(copy_to_cur_active);
    while(true) {
continue_lbl:
        r = link(prev_r);
        
        // << If node |r| is of type |DELTA_NODE|, update |cur_active_width|, set |prev_r| and |prev_prev_r|, then |goto continue| >>

        // << If a line number class has ended, create new active nodes for the best feasible breaks in that class; then |return| if |r = LAST_ACTIVE|, otherwise compute the new |line_width| >>
        
        // << Consider the demerits for a line from |r| to |cur_p|; deactivate node |r| if it should no longer be active; then |goto continue| if a line from |r| to |cur_p| is infeasible, otherwise record a new feasible break >>
    }
end:
#ifdef STAT
    // << Update the value of |printed_node| for symbolic displays >>
#endif
}
```
