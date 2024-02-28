# Section 830

```c << Other local variables for |try_break| >>=
pointer prev_prev_r = null; // a step behind |prev_r|, if |type(prev_r) = DELTA_NODE|
pointer s;                  // runs through nodes ahead of |cur_p|
pointer q;                  // points to a new node being created
pointer v;                  // points to a glue specification or a node ahead of |cur_p|
int t;                      // node count, if |cur_p| is a discretionary node
internal_font_number f;     // used in character width calculation
halfword l;                 // line number of current active node
bool node_r_stays_active;   // should node |r| remain in the active list?
scaled line_width = 0;      // the current line will be justified to this width
int fit_class;              // possible fitness class of test line
halfword b;                 // badness of test line
int d;                      // demerits of test line
bool artificial_demerits;   // has |d| been forced to zero?
#ifdef STAT
pointer save_link;          // temporarily holds value of |link(cur_p)|
#endif
scaled shortfall;           // used in badness calculations
```
