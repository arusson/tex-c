# Section 93

The following procedure prints $\TeX$'s last words before dying.

```c error.c
void succumb() {
    if (interaction == ERROR_STOP_MODE) {
        interaction = SCROLL_MODE; // no more interaction
    }
    if (log_opened) {
        error();
    }
#ifdef DEBUG
    if (interaction > BATCH_MODE) {
        debug_help();
    }
#endif
    history = FATAL_ERROR_STOP;
    jump_out(); // irrecoverable error
}

// prints |s| and that's it
void fatal_error(char *s) {
    normalize_selector();
    print_err("Emergency stop");
    help1(s);
    succumb();
}
```
