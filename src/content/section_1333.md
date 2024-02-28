# Section 1333

Here we do whatever is needed to complete $\TeX$'s job gracefully on the local operating system.
The code here might come into play after a fatal error; it must therefore consist entirely of "safe" operations that cannot produce error messages.
For example, it would be a mistake to call *str_room* or *make_string* at this time, because a call on *overflow* might lead to an infinite loop.
(Actually there's one way to get error messages, via *prepare_mag*;
but that can't cause infinite recursion.)

If *final_cleanup* is bypassed, this program doesn't bother to close the input files that may still be open.

```c << Last-minute procedures >>=
void close_files_and_terminate() {
    int k; // all-purpose index
    // << Finish the extensions >>
    new_line_char = -1;
#ifdef STAT
    if (tracing_stats > 0) {
        // << Output statistics about this job >>
    }
#endif
    // << Finish the DVI file >>
    if (log_opened) {
        wlog_cr;
        a_close(log_file);
        selector -= 2;
        if (selector == TERM_ONLY) {
            print_nl("Transcript written on ");
            slow_print(log_name);
            print_char('.');
            print_ln();
        }
    }
}
```
