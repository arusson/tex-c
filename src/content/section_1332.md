# Section 1332

Now this is really it: $\TeX$ starts and ends here.

The initial test involving *ready_already* should be deleted if the Pascal runtime system is smart enough to detect such a "mistake".

```c main.c
// << Start file |main.c| >>

// |start_here|
int main(int argc, char *argv[]) {
    history = FATAL_ERROR_STOP; // in case we quit during initialization
    // if ready_already = 314159 then goto start_of_TEX
    // << Check the "constant" values for consistency >>
    if (bad > 0) {
        printf(
            "Ouch---my internal constants have been clobbered!" "---case %d\n", bad
        );
        exit(0);
    }
    initialize(); // set global variables to their starting values
#ifdef INIT
    get_strings_started();
    init_prim(); // call |primitive| for each primitive
    init_str_ptr = str_ptr;
    init_pool_ptr = pool_ptr;
    fix_date_and_time();
#endif
    // ready_already = 314159; Sorry, not supported
    // start_of_TEX:
    // << Initialize the output routines >>
    // << Get the first line of input and prepare to start >>
    history = SPOTLESS; // ready to go!
    main_control();     // come to life
    final_cleanup();    // prepare for death
    // end_of_TEX:
    close_files_and_terminate();
    return 0;
}
```
