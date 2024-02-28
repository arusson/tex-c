# Section 96

Users occasionally want to interrupt $\TeX$ while it's running.
If the Pascal runtime system allows this, one can implement a routine that sets the global variable *interrupt* to some nonzero value when such an interrupt is signalled.
Otherwise there is probably at least a way to make *interrupt* nonzero using the Pascal debugger.

```c include/texerror.h
#define check_interrupt               \
    do {                              \
        if (interrupt != 0) {         \
            pause_for_instructions(); \
        }                             \
    } while (0)
```

```c << Global variables >>+=
int interrupt;        // should TeX pause for instructions?
bool ok_to_interrupt; // should interrupts be observed?
```
