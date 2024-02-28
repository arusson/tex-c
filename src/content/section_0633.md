# Section 633

```c << Output a rule in a vlist, |goto next_p| >>=
if (is_running(rule_wd)) {
    rule_wd = width(this_box);
}
rule_ht += rule_dp; // this is the rule thickness
cur_v += rule_ht;
if (rule_ht > 0 && rule_wd > 0) {
    // we don't output empty rules
    synch_h;
    synch_v;
    dvi_out(PUT_RULE);
    dvi_four(rule_ht);
    dvi_four(rule_wd);
}
goto next_p;
```
