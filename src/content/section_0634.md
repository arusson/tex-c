# Section 634

```c << Move down or output leaders >>=
g = glue_ptr(p);
rule_ht = width(g) - cur_g;
if (g_sign != NORMAL) {
    if (g_sign == STRETCHING) {
        if (stretch_order(g) == g_order) {
            cur_glue += stretch(g);
            vet_glue(glue_set(this_box)*cur_glue);
            cur_g = (scaled)round(glue_temp);
        }
    }
    else if (shrink_order(g) == g_order) {
        cur_glue -= shrink(g);
        vet_glue(glue_set(this_box)*cur_glue);
        cur_g = (scaled)round(glue_temp);
    }
}
rule_ht += cur_g;
if (subtype(p) >= A_LEADERS) {
    // << Output leaders in a vlist, |goto fin_rule| if a rule or to |next_p| if done >>
}
goto move_past;
```
