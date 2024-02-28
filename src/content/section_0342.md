# Section 342

An alignment entry ends when a tab or `\cr` occurs, provided that the current level of braces is the same as the level that was present at the beginning of that alignment entry;
i.e., provided that *align_state* has returned to the value it had after the $\langle u_j\rangle$ template for that entry.

```c << If an alignment entry has just ended, take appropriate action >>=
if (cur_cmd <= CAR_RET
    && cur_cmd >= TAB_MARK
    && align_state == 0)
{
    // << Insert the <v_j> template and |goto restart| >>
}
```
