# Section 387

Now let's consider *MACRO_CALL* itself, which is invoked when $\TeX$ is scanning a control sequence whose *cur_cmd* is either *CALL*, *LONG_CALL*, *OUTER_CALL*, or *LONG_OUTER_CALL*.
The control sequence definition appears in the token list whose reference count is in location *cur_chr* of *mem*.

The global variable *long_state* will be set to *CALL* or to *LONG_CALL*, depending on whether or not the control sequence disallows `\par` in its parameters.
The *get_next* routine will set *long_state* to *OUTER_CALL* and emit `\par`, if a file ends or if an `\outer` control sequence occurs in the midst of an argument.

```c << Global variables >>+=
int long_state; // governs the acceptance of \par
```
