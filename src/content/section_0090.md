# Section 90

```c << Put help message on the transcript file >>=
if (interaction > BATCH_MODE) {
    decr(selector); // avoid terminal output
}
if (use_err_help) {
    print_ln();
    give_err_help();
}
else {
    while (help_ptr > 0) {
        decr(help_ptr);
        print_nl(help_line[help_ptr]);
    }
}
print_ln();
if (interaction > BATCH_MODE) {
    incr(selector); // re-enable terminal output
}
print_ln();
```
