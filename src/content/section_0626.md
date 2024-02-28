# Section 626

```c << Output leaders in an hlist, |goto fin_rule| if a rule or to |next_p| if done >>=
leader_box = leader_ptr(p);
if (type(leader_box) == RULE_NODE) {
    rule_ht = height(leader_box);
    rule_dp = depth(leader_box);
    goto fin_rule;
}
leader_wd = width(leader_box);
if (leader_wd > 0 && rule_wd > 0) {
    rule_wd += 10; // compensate for floating - point rounding
    edge = cur_h + rule_wd;
    lx = 0;
    // << Let |cur_h| be the position of the first box, and set |leader_wd + lx| to the spacing between corresponding parts of boxes >>
    while (cur_h + leader_wd <= edge) {
        // << Output a leader box at |cur_h|, then advance |cur_h| by |leader_wd + lx| >>
    }
    cur_h = edge - 10;
    goto next_p;
}
```
