# Section 828

A pointer variable *cur_p* runs through the given horizontal list as we look for breakpoints.
This variable is global, since it is used both by *line_break* and by its subprocedure *try_break*.

Another global variable called *threshold* is used to determine the feasibility of individual lines:
Breakpoints are feasible if there is a way to reach them without creating lines whose badness exceeds *threshold*.
(The badness is compared to *threshold* before penalties are added, so that penalty values do not affect the feasibility of breakpoints, except that no break is allowed when the penalty is 10000 or more.)
If *threshold* is 10000 or more, all legal breaks are considered feasible, since the *badness* function specified above never returns a value greater than&nbsp;10000.

Up to three passes might be made through the paragraph in an attempt to find at least one set of feasible breakpoints.
On the first pass, we have *threshold = pretolerance* and *second_pass = final_pass = false*.
If this pass fails to find a feasible solution, *threshold* is set to *tolerance*, *second_pass* is set *true*, and an attempt is made to hyphenate as many words as possible.
If that fails too, we add *emergency_stretch* to the background stretchability and set *final_pass = true*.

```c << Global variables >>+=
pointer cur_p;    // the current breakpoint under consideration
bool second_pass; // is this our second attempt to break this paragraph?
bool final_pass;  // is this our final attempt to break this paragraph?
int threshold;    // maximum badness on feasible lines
```
