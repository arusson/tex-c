# Section 629

The *vlist_out* routine is similar to *hlist_out*, but a bit simpler.

```c dvi.c
// output a |VLIST_NODE| box
void vlist_out() {
    scaled left_edge;         // the left coordinate for this box
    scaled top_edge;          // the top coordinate for this box
    scaled save_h, save_v;    // what |dvi_h| and |dvi_v| should pop to
    pointer this_box;         // pointer to containing box
    int g_order;              // applicable order of infinity for glue
    int g_sign;               // selects type of glue
    pointer p;                // current position in the vlist
    int save_loc;             // `DVI` byte location upon entry
    pointer leader_box;       // the leader box being replicated
    scaled leader_ht;         // height of leader box being replicated
    scaled lx;                // extra space between leader boxes
    bool outer_doing_leaders; // were we doing leaders?
    scaled edge;              // bottom boundary of leader space
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
    left_edge = cur_h;
    cur_v -= height(this_box);
    top_edge = cur_v;
    while (p != null) {
        // << Output node |p| for |vlist_out| and move to the next node, maintaining the condition |cur_h = left_edge| >>
    }
    prune_movements(save_loc);
    if (cur_s > 0) {
        dvi_pop(save_loc);
    }
    decr(cur_s);
}
```
