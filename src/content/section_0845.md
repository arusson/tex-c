# Section 845

When we create an active node, we also create the corresponding passive node.

```c << Insert a new active node from |best_place[fit_class]| to |cur_p| >>=
q = get_node(PASSIVE_NODE_SIZE);
link(q) = passive;
passive = q;
cur_break(q) = cur_p;
#ifdef STAT
incr(pass_number);
serial(q) = pass_number;
#endif
prev_break(q) = best_place[fit_class];
q = get_node(ACTIVE_NODE_SIZE);
break_node(q) = passive;
line_number(q) = best_pl_line[fit_class] + 1;
fitness(q) = fit_class;
type(q) = break_type;
total_demerits(q) = minimal_demerits[fit_class];
link(q) = r;
link(prev_r) = q;
prev_r = q;
#ifdef STAT
if (tracing_paragraphs > 0) {
    // << Print a symbolic description of the new break node >>
}
#endif
```
