# Section 862: Breaking paragraphs into lines, continued

So far we have gotten a little way into the *line_break* routine, having covered its important *try_break* subroutine.
Now let's consider the rest of the process.

The main loop of *line_break* traverses the given hlist, starting at *link(TEMP_HEAD)*, and calls *try_break* at each legal breakpoint.
A variable called *auto_breaking* is set to true except within math formulas, since glue nodes are not legal breakpoints when they appear in formulas.

The current node of interest in the hlist is pointed to by *cur_p*.
Another variable, *prev_p*, is usually one step behind *cur_p*, but the real meaning of *prev_p* is this: If *type(cur_p) = GLUE_NODE* then *cur_p* is a legal breakpoint if and only if *auto_breaking* is true and *prev_p* does not point to a glue node, penalty node, explicit kern node, or math node.

The following declarations provide for a few other local variables that are used in special calculations.

```c << Local variables for line breaking >>=
bool auto_breaking;      // is node |cur_p| outside a formula?
pointer prev_p;          // helps to determine when glue nodes are breakpoints
pointer q, r, s, prev_s; // miscellaneous nodes of temporary interest
internal_font_number f;  // used when calculating character widths
```
