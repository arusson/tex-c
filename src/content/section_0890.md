# Section 890

Penalties between the lines of a paragraph come from club and widow lines, from the *inter_line_penalty* parameter, and from lines that end at discretionary breaks.
Breaking between lines of a two-line paragraph gets both club-line and widow-line penalties.
The local variable *pen* will be set to the sum of all relevant penalties for the current line, except that the final line is never penalized.

```c << Append a penalty node, if a nonzero penalty is appropriate >>=
if (cur_line + 1 != best_line) {
    pen = inter_line_penalty;
    if (cur_line == prev_graf + 1) {
        pen += club_penalty;
    }
    if (cur_line + 2 == best_line) {
        pen += final_widow_penalty;
    }
    if (disc_break) {
        pen += broken_penalty;
    }
    if (pen != 0) {
        r = new_penalty(pen);
        link(tail) = r;
        tail = r;
    }
}
```
