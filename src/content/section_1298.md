# Section 1298

```c << Complete a potentially long \show command >>=
end_diagnostic(true);
print_err("OK");
if (selector == TERM_AND_LOG && tracing_online <= 0) {
    selector = TERM_ONLY;
    print(" (see the transcript file)");
    selector = TERM_AND_LOG;
}
```
