# Section 864

The active node that represents the starting point does not need a corresponding passive node.

```c include/breaker.h
#define store_background(X) active_width[(X)] = background[(X)]
```

```c << Create an active breakpoint representing the beginning of the paragraph >>=
q = get_node(ACTIVE_NODE_SIZE);
type(q) = UNHYPHENATED;
fitness(q) = DECENT_FIT;
link(q) = LAST_ACTIVE;
break_node(q) = null;
line_number(q) = prev_graf + 1;
total_demerits(q) = 0;
link(ACTIVE) = q;
do_all_six(store_background);
passive = null;
printed_node = TEMP_HEAD;
pass_number = 0;
font_in_short_display = NULL_FONT;
```
