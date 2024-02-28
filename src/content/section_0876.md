# Section 876

Once the best sequence of breakpoints has been found (hurray), we call on the procedure *post_line_break* to finish the remainder of the work.
(By introducing this subprocedure, we are able to keep *line_break* from getting extremely long.)

```c << Break the paragraph at the chosen breakpoints, justify the resulting lines to the correct widths, and append them to the current vertical list >>=
post_line_break(final_widow_penalty);
```
