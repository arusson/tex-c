# Section 624

```c << Output a rule in an hlist >>=
if (is_running(rule_ht)) {
    rule_ht = height(this_box);
}
if (is_running(rule_dp)) {
    rule_dp = depth(this_box);
}
rule_ht += rule_dp; // this is the rule thickness
if (rule_ht > 0 && rule_wd > 0) {
    // we don't output empty rules
    synch_h;
    cur_v = base_line + rule_dp;
    synch_v;
    dvi_out(SET_RULE);
    dvi_four(rule_ht);
    dvi_four(rule_wd);
    cur_v = base_line;
    dvi_h += rule_wd;
}
```
