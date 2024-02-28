# Section 619

The recursive procedures *hlist_out* and *vlist_out* each have local variables *save_h* and *save_v* to hold the values of *dvi_h* and *dvi_v* just before entering a new level of recursion.
 In effect, the values of *save_h* and *save_v* on $\TeX$'s run-time stack correspond to the values of *h* and *v*
that a `DVI`-reading program will push onto its coordinate stack.

```c dvi.c
// << Declare procedures needed in |hlist_out|, |vlist_out| >>

// output an |HLIST_NODE| box
void hlist_out() {
    scaled base_line;         // the baseline coordinate for this box
    scaled left_edge;         // the left coordinate for this box
    scaled save_h, save_v;    // what |dvi_h| and |dvi_v| should pop to
    pointer this_box;         // pointer to containing box
    int g_order;              // applicable order of infinity for glue
    int g_sign;               // selects type of glue
    pointer p;                // current position in the hlist
    int save_loc;             // `DVI` byte location upon entry
    pointer leader_box;       // the leader box being replicated
    scaled leader_wd;         // width of leader box being replicated
    scaled lx;                // extra space between leader boxes
    bool outer_doing_leaders; // were we doing leaders?
    scaled edge;              // left edge of sub-box, or right edge of leader space
    double glue_temp;         // glue value before rounding
    double cur_glue;          // glue seen so far
    scaled cur_g;             // rounded equivalent of |cur_glue| times the glue ratio
    
    cur_g = 0;
    cur_glue = 0.0;
    this_box = temp_ptr;
    g_order = glue_order(this_box);
    g_sign = glue_sign(this_box);
    p = list_ptr(this_box);
    incr(cur_s);
    if (cur_s > 0) {
        dvi_out(PUSH);
    }
    if (cur_s > max_push) {
        max_push = cur_s;
    }
    save_loc = dvi_offset + dvi_ptr;
    base_line = cur_v;
    left_edge = cur_h;
    while (p != null) {
        // << Output node |p| for |hlist_out| and move to the next node, maintaining the condition |cur_v = base_line| >>
    }
    prune_movements(save_loc);
    if (cur_s > 0) {
        dvi_pop(save_loc);
    }
    decr(cur_s);
}
```
