# Section 816

The first task is to move the list from *head* to *TEMP_HEAD* and go into the enclosing semantic level.
We also append the `\parfillskip` glue to the end of the paragraph, removing a space (or other glue node) if it was there, since spaces usually precede blank lines and instances of '`$$`'.
The *par_fill_skip* is preceded by an infinite penalty, so it will never be considered as a potential breakpoint.

This code assumes that a *GLUE_NODE* and a *PENALTY_NODE* occupy the same number of *mem*&nbsp;words.

```c << Get ready to start line breaking >>=
link(TEMP_HEAD) = link(head);
if (is_char_node(tail)) {
    tail_append(new_penalty(INF_PENALTY));
}
else if (type(tail) != GLUE_NODE) {
    tail_append(new_penalty(INF_PENALTY));
}
else {
    type(tail) = PENALTY_NODE;
    delete_glue_ref(glue_ptr(tail));
    flush_node_list(leader_ptr(tail));
    penalty(tail) = INF_PENALTY;
}
link(tail) = new_param_glue(PAR_FILL_SKIP_CODE);
init_cur_lang = prev_graf % 0x10000;
init_l_hyf = prev_graf / 0x400000;
init_r_hyf = (prev_graf / 0x10000) % 64;
pop_nest();
```
