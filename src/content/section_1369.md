# Section 1369

To write a token list, we must run it through $\TeX$'s scanner, expanding macros and `\the` and `\number`, etc.
This might cause runaways, if a delimited macro parameter isn't matched, and runaways would be extremely confusing since we are calling on $\TeX$'s scanner in the middle of a `\shipout` command.
Therefore we will put a dummy control sequence as a "stopper", right after the token list.
This control sequence is artificially defined to be `\outer`.

> ![NOTE]
> String `"endwrite"` must be added to the pool.

```c << Read the other strings >>+=
put_string("endwrite"); // ENDWRITE_STRING: 271
```

```c << Internal strings numbers in the pool >>+=
#define ENDWRITE_STRING 271
```

```c << Initialize table entries (done by INITEX only) >>+=
text(END_WRITE) = ENDWRITE_STRING; // "endwrite"
eq_level(END_WRITE) = LEVEL_ONE;
eq_type(END_WRITE) = OUTER_CALL;
equiv(END_WRITE) = null;
```
