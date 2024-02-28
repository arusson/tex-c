# Section 823

As the algorithm runs, it maintains a set of six delta-like registers for the length of the line following the first active breakpoint to the current position in the given hlist.
When it makes a pass through the active list, it also maintains a similar set of six registers for the length following the active breakpoint of current interest.
A third set holds the length of an empty line (namely, the sum of `\leftskip` and `\rightskip`); and a fourth set is used to create new delta nodes.

When we pass a delta node we want to do operations like

<div align="center">

**for** *k &larr; 1* **to** *6* **do** *cur_active_width[k]* &larr; *cur_active_width[k] + mem[q + k].sc*;
</div>

and we want to do this without the overhead of **for** loops.
The *do_all_six* macro makes such six-tuples convenient.

```c include/breaker.h
#define do_all_six(X) X(1); X(2); X(3); X(4); X(5); X(6)
```

```c << Global variables >>+=
// distance from first active node to |cur_p|
scaled active_width0[6];
scaled *active_width = active_width0 - 1;

// distance from current active node
scaled cur_active_width0[6];
scaled *cur_active_width = cur_active_width0 - 1;

// length of an "empty" line
scaled background0[6];
scaled *background = background0 - 1;

// length being computed after current break
scaled break_width0[6];
scaled *break_width = break_width0 - 1;
```
