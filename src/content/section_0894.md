# Section 894

When the following code is activated, the *line_break* procedure is in its second pass, and *cur_p* points to a glue node.

```c << Try to hyphenate the following word >>=
prev_s = cur_p;
s = link(prev_s);
if (s != null) {
    // << Skip to node |ha|, or |goto done1| if no hyphenation should be attempted >>
    if (l_hyf + r_hyf > 63) {
        goto done1;
    }
    // << Skip to node |hb|, putting letters into |hu| and |hc| >>
    // << Check that the nodes following |hb| permit hyphenation and that at least |l_hyf + r_hyf| letters have been found, otherwise |goto done1| >>
    hyphenate();
}
done1:
```
