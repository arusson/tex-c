# Section 395

```c << Report an extra right brace and |goto continue| >>=
back_input();
print_err("Argument of ");
sprint_cs(warning_index);
print(" has an extra }");
help6("I've run across a `}' that doesn't seem to match anything.")
    ("For example, `\\def\\a#1{...}' and `\\a}' would produce")
    ("this error. If you simply proceed now, the `\\par' that")
    ("I've just inserted will cause me to report a runaway")
    ("argument that might be the root of the problem. But if")
    ("your `}' was spurious, just type `2' and it will go away.");
incr(align_state);
long_state = CALL;
cur_tok = par_token;
ins_error();
goto continue_lbl;
// a white lie; the \par won't always trigger a runaway
```
