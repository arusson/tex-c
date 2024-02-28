# Section 858

When the data for a discretionary break is being displayed, we will have printed the *pre_break* and *post_break* lists; we want to skip over the third list, so that the discretionary data will not appear twice.
The following code is performed at the very end of *try_break*.

```c << Update the value of |printed_node| for symbolic displays >>=
if (cur_p == printed_node
    && cur_p != null
    && type(cur_p) == DISC_NODE)
{
    t = replace_count(cur_p);
    while (t > 0) {
        decr(t);
        printed_node = link(printed_node);
    }
}
```
