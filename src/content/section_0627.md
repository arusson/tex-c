# Section 627

The calculations related to leaders require a bit of care.
First, in the case of *A_LEADERS* (aligned leaders), we want to move *cur_h* to *left_edge* plus the smallest multiple of *leader_wd* for which the result is not less than the current value of *cur_h*; i.e., *cur_h* should become
*left_edge* + *leader_wd* $\times\lceil$(*cur_h* − *left_edge*)/*leader_wd*$\rceil$.
The program here should work in all cases even though some implementations of Pascal give nonstandard results for the **div** operation when *cur_h* is less than *left_edge*.

In the case of *C_LEADERS* (centered leaders), we want to increase *cur_h* by half of the excess space not occupied by the leaders; and in the case of *X_LEADERS* (expanded leaders) we increase *cur_h* by *1*$/$*(q + 1)* of this excess space, where *q* is the number of times the leader box will be replicated.
Slight inaccuracies in the division might accumulate; half of this rounding error is placed at each end of the leaders.

```c << Let |cur_h| be the position of the first box, and set |leader_wd + lx| to the spacing between corresponding parts of boxes >>=
if (subtype(p) == A_LEADERS) {
    save_h = cur_h;
    cur_h = left_edge + leader_wd*((cur_h - left_edge) / leader_wd);
    if (cur_h < save_h) {
        cur_h += leader_wd;
    }
}
else {
    lq = rule_wd / leader_wd; // the number of box copies
    lr = rule_wd % leader_wd; // the remaining space
    if (subtype(p) == C_LEADERS) {
        cur_h += lr / 2;
    }
    else {
        lx = lr / (lq + 1);
        cur_h += (lr - (lq - 1) * lx) / 2;
    }
}
```
