# Section 1338: Debugging

Once $\TeX$ is working, you should be able to diagnose most errors with the `\show` commands and other diagnostic features.
But for the initial stages of debugging, and for the revelation of really deep mysteries, you can compile $\TeX$ with a few more aids, including the Pascal runtime checks and its debugger.
An additional routine called *debug_help* will also come into play when you type '`D`' after an error message;
*debug_help* also occurs just before a fatal error causes $\TeX$ to succumb.

The interface to *debug_help* is primitive, but it is good enough when used with a Pascal debugger that allows you to set breakpoints and to read variables and change their values.
After getting the prompt '`debug #`', you type either a negative number (this exits *debug_help*), or zero (this goes to a location where you can set a breakpoint, thereby entering into dialog with the Pascal debugger), or a positive number *m* followed by an argument *n*.
The meaning of *m* and *n* will be clear from the program below.
(If *m = 13*, there is an additional argument, *l*.)

```c << Last-minute procedures >>+=
#ifdef DEBUG
 // routine to display various things
void debug_help() {
    int k, l, m, n;
    int err; // handling input error
    clear_terminal;
    while(true) {
        print_nl("debug # (-1 to exit):");
        update_terminal;
        err = scanf("%d", &m);
        if (err != 1) {
            print("?");
            continue;
        }
        if (m < 0) {
            return;
        }
        err = scanf("%d", &n);
        if (err != 1) {
            print("?");
            continue;
        }
        switch (m) {
        // << Numbered cases for |debug_help| >>
        
        default:
            print("?");
        }
    }
}
#endif
```
