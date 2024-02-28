# Section 396

If *long_state = OUTER_CALL*, a runaway argument has already been reported.

```c << Report a runaway argument and abort >>=
if (long_state == CALL) {
    runaway();
    print_err("Paragraph ended before ");
    sprint_cs(warning_index);
    print(" was complete");
    help3("I suspect you've forgotten a `}', causing me to apply this")
        ("control sequence to too much text. How can we recover?")
        ("My plan is to forget the whole thing and hope for the best.");
    back_error();
}
pstack[n] = link(TEMP_HEAD);
align_state -= unbalance;
for(m = 0; m <= n; m++) {
    flush_list(pstack[m]);
}
goto end;
```
