# Section 637

When we reach this part of the program, *cur_v* indicates the top of a leader box, not its baseline.

```c << Output a leader box at |cur_v|, then advance |cur_v| by |leader_ht + lx| >>=
cur_h = left_edge + shift_amount(leader_box);
synch_h;
save_h = dvi_h;
cur_v += height(leader_box);
synch_v;
save_v = dvi_v;
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
cur_h = left_edge;
cur_v = save_v - height(leader_box) + leader_ht + lx;
```
