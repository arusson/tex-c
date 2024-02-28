# Section 400

If the parameter consists of a single group enclosed in braces, we must strip off the enclosing braces.
That's why *rbrace_ptr* was introduced.

```c << Tidy up the parameter just scanned, and tuck it away >>=
if (m == 1 && info(p) < RIGHT_BRACE_LIMIT) {
    link(rbrace_ptr) = null;
    free_avail(p);
    p = link(TEMP_HEAD);
    pstack[n] = link(p);
    free_avail(p);
}
else {
    pstack[n] = link(TEMP_HEAD);
}
incr(n);
if (tracing_macros > 0) {
    begin_diagnostic();
    print_nl_strnumber(match_chr);
    print_int(n);
    print("<-");
    show_token_list(pstack[n - 1], null, 1000);
    end_diagnostic(false);
}
```
