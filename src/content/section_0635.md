# Section 635

```c << Output leaders in a vlist, |goto fin_rule| if a rule or to |next_p| if done >>=
leader_box = leader_ptr(p);
if (type(leader_box) == RULE_NODE) {
    rule_wd = width(leader_box);
    rule_dp = 0;
    goto fin_rule;
}
leader_ht = height(leader_box) + depth(leader_box);
if (leader_ht > 0 && rule_ht > 0) {
    rule_ht += 10; // compensate for floating - point rounding
    edge = cur_v + rule_ht;
    lx = 0;
    // << Let |cur_v| be the position of the first box, and set |leader_ht + lx| to the spacing between corresponding parts of boxes >>
    while (cur_v + leader_ht <= edge) {
        // << Output a leader box at |cur_v|, then advance |cur_v| by |leader_ht + lx| >>
    }
    cur_v = edge - 10;
    goto next_p;
}
```
