# Section 1196

The *unsave* is done after everything else here; hence an appearance of '`\mathsurround`' inside of '`$...$`' affects the spacing at these particular `$`'s.
This is consistent with the conventions of <span style="white-space: nowrap;">'`$$...$$`'</span>, since '`\abovedisplayskip`' inside a display affects the space above that display.

```c << Finish math in text >>=
tail_append(new_math(math_surround, BEFORE));
cur_mlist = p;
cur_style = TEXT_STYLE;
mlist_penalties = (mode > 0);
mlist_to_hlist();
link(tail) = link(TEMP_HEAD);
while (link(tail) != null) {
    tail = link(tail);
}
tail_append(new_math(math_surround, AFTER));
space_factor = 1000;
unsave();
```
