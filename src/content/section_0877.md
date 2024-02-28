# Section 877

The total number of lines that will be set by *post_line_break* is *best_line − prev_graf − 1*.
The last breakpoint is specified by *break_node(best_bet)*, and this passive node points to the other breakpoints via the *prev_break* links.
The finishing-up phase starts by linking the relevant passive nodes in forward order, changing *prev_break* to *next_break*.
(The *next_break* fields actually reside in the same memory space as the *prev_break* fields did, but we give them a new name because of their new significance.) Then the lines are justified, one by one.

```c include/breaker.h
#define next_break prev_break // new name for |prev_break| after links are reversed
```

```c << Declare subprocedures for |line_break| >>+=
void post_line_break(int final_widow_penalty) {
    pointer q, r, s;      // temporary registers for list manipulation
    bool disc_break;      // was the current break at a discretionary node?
    bool post_disc_break; // and did it have a nonempty post-break part?
    scaled cur_width;     // width of line number |cur_line|
    scaled cur_indent;    // left margin of line number |cur_line|
    quarterword t;        // used for replacement counts in discretionary nodes
    int pen;              // use when calculating penalties between lines
    halfword cur_line;    // the current line number being justified
    
    // << Reverse the links of the relevant passive nodes, setting |cur_p| to the first breakpoint >>
    cur_line = prev_graf + 1;
    do {
        // << Justify the line ending at breakpoint |cur_p|, and append it to the current vertical list, together with associated penalties and other insertions >>
        incr(cur_line);
        cur_p = next_break(cur_p);
        if (cur_p != null && !post_disc_break) {
            // << Prune unwanted nodes at the beginning of the next line >>
        }
    } while (cur_p != null);
    if (cur_line != best_line || link(TEMP_HEAD) != null) {
        confusion("line breaking");
    }
    prev_graf = best_line - 1;
}
```
