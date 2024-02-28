# Section 486

An empty line is appended at the end of a *read_file*.

```c << Input the next line of |read_file[m]| >>=
if (!input_ln(read_file[m])) {
    a_close(read_file[m]);
    read_open[m] = CLOSED;
    if (align_state != 1000000) {
        runaway();
        print_err("File ended within ");
        print_esc("read");
        help1("This \\read has unbalanced braces.");
        align_state = 1000000;
        limit = 0;
        error();
    }
}
```
