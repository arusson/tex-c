# Section 348

When a character of type *SPACER* gets through, its character code is changed to '␣' = 32.
This means that the ASCII codes for tab and space, and for the space inserted at the end of a line, will be treated alike when macro parameters are being matched.
We do this since such characters are indistinguishable on most computer terminal displays.

```c << Finish line, emit a space >>=
loc = limit + 1;
cur_cmd = SPACER;
cur_chr = ' ';
```
