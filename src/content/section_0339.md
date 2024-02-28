# Section 339

The recovery procedure can't be fully understood without knowing more about the $\TeX$ routines that should be aborted, but we can sketch the ideas here:
For a runaway definition or a runaway balanced text we will insert a right brace;
for a runaway preamble, we will insert a special `\cr` token and a right brace;
and for a runaway argument, we will set *long_state* to *OUTER_CALL* and insert `\par`.

```c << Print either 'definition' or 'use' or 'preamble' or 'text', and insert tokens that should lead to recovery >>=
p = get_avail();
switch (scanner_status) {
case DEFINING:
    print("definition");
    info(p) = RIGHT_BRACE_TOKEN + '}';
    break;

case MATCHING:
    print("use");
    info(p) = par_token;
    long_state = OUTER_CALL;
    break;

case ALIGNING:
    print("preamble");
    info(p) = RIGHT_BRACE_TOKEN + '}';
    q = p;
    p = get_avail();
    link(p) = q;
    info(p) = CS_TOKEN_FLAG + FROZEN_CR;
    align_state = -1000000;
    break;

case ABSORBING:
    print("text");
    info(p) = RIGHT_BRACE_TOKEN + '}';
} // there are no other cases
ins_list(p);
```
