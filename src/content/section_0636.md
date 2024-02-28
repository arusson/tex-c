# Section 636

```c << Let |cur_v| be the position of the first box, and set |leader_ht + lx| to the spacing between corresponding parts of boxes >>=
if (subtype(p) == A_LEADERS) {
    save_v = cur_v;
    cur_v = top_edge + leader_ht*((cur_v - top_edge) / leader_ht);
    if (cur_v < save_v) {
        cur_v += leader_ht;
    }
}
else {
    lq = rule_ht / leader_ht; // the number of box copies
    lr = rule_ht % leader_ht; // the remaining space
    if (subtype(p) == C_LEADERS) {
        cur_v += lr / 2;
    }
    else {
        lx = lr / (lq + 1);
        cur_v += (lr - (lq - 1) * lx)/2;
    }
}
```
