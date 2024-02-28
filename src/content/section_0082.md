# Section 82

Here now is the general *error* routine.

```c error.c
void error() {
    ASCII_code c;       // what the user types
    int s1, s2, s3, s4; // used to save global variables when deleting tokens
    if (history < ERROR_MESSAGE_ISSUED) {
        history = ERROR_MESSAGE_ISSUED;
    }
    print_char('.');
    show_context();
    if (interaction == ERROR_STOP_MODE) {
        // << Get user's advice and |return| >>
    }
    incr(error_count);
    if (error_count == 100) {
        print_nl("(That makes 100 errors; please try again.)");
        history = FATAL_ERROR_STOP;
        jump_out();
    }
    // << Put help message on the transcript file >>
}
```
