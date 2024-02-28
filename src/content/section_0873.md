# Section 873

```c << Try the final line break at the end of the paragraph, and |goto done| if the desired breakpoints have been found >>=
try_break(EJECT_PENALTY, HYPHENATED);
if (link(ACTIVE) != LAST_ACTIVE) {
    // << Find an active node with fewest demerits >>
    if (looseness == 0) {
        goto done;
    }
    // << Find the best active node for the desired looseness >>
    if (actual_looseness == looseness || final_pass) {
        goto done;
    }
}
```
