# Section 92

In anomalous cases, the print selector might be in an unknown state;
the following subroutine is called to fix things just enough to keep running a bit longer.

```c error.c
void normalize_selector() {
    if (log_opened) {
        selector = TERM_AND_LOG;
    }
    else {
        selector = TERM_ONLY;
    }

    if (job_name == 0) {
        open_log_file();
    }
    if (interaction == BATCH_MODE) {
        decr(selector);
    }
}
```
