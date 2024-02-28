# Section 878

The job of reversing links in a list is conveniently regarded as the job of taking items off one stack and putting them on another.
In this case we take them off a stack pointed to by *q* and having *prev_break* fields;
we put them on a stack pointed to by *cur_p* and having *next_break* fields. Node *r* is the passive node being moved from stack to stack.

```c << Reverse the links of the relevant passive nodes, setting |cur_p| to the first breakpoint >>=
q = break_node(best_bet);
cur_p = null;
do {
    r = q;
    q = prev_break(q);
    next_break(r) = cur_p;
    cur_p = r;
} while (q != null);
```
