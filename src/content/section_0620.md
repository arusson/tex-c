# Section 620

We ought to give special care to the efficiency of one part of *hlist_out*, since it belongs to $\TeX$'s inner loop.
When a *CHAR_NODE* is encountered, we save a little time by processing several nodes in succession until reaching a non-*CHAR_NODE*.
The program uses the fact that *SET_CHAR_0 = 0*.

```c << Output node |p| for |hlist_out| and move to the next node, maintaining the condition |cur_v = base_line| >>=
reswitch:
if (is_char_node(p)) {
    synch_h;
    synch_v;
    do {
        f = font(p);
        c = character(p);
        if (f != dvi_f) {
            // << Change font |dvi_f| to |f| >>
        }
        if (c >= 128) {
            dvi_out(SET1);
        }
        dvi_out(c);
        cur_h += char_width(f, char_info(f, c));
        p = link(p);
  } while (is_char_node(p));
  dvi_h = cur_h;
}
else {
    // << Output the non-|CHAR_NODE| |p| for |hlist_out| and move to the next node >>
}
```
