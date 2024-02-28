# Section 831

```c << Make sure that |pi| is in the proper range >>=
if (abs(pi) >= INF_PENALTY) {
    if (pi > 0) {
        goto end; // this breakpoint is inhibited by infinite penalty
    }
    else {
        pi = EJECT_PENALTY; // this breakpoint will be forced
    }
}
```
