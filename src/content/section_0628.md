# Section 628

The *'synch'* operations here are intended to decrease the number of bytes needed to specify horizontal and vertical motion in the `DVI` output.

```c <<  Output a leader box at |cur_h|, then advance |cur_h| by |leader_wd + lx| >>=
cur_v = base_line + shift_amount(leader_box);
synch_v;
save_v = dvi_v;
synch_h;
save_h = dvi_h;
temp_ptr = leader_box;
outer_doing_leaders = doing_leaders;
doing_leaders = true;
if (type(leader_box) == VLIST_NODE) {
    vlist_out();
}
else {
    hlist_out();
}
doing_leaders = outer_doing_leaders;
dvi_v = save_v;
dvi_h = save_h;
cur_v = base_line;
cur_h = save_h + leader_wd + lx;
```
