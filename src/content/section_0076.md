# Section 76

A global variable *deletions_allowed* is set *false* if the *get_next* routine is active when *error* is called;
this ensures that *get_next* and related routines like *get_token* will never be called recursively.
A similar interlock is provided by *set_box_allowed*.

The global variable *history* records the worst level of error that has been detected.
It has four possible values: *SPOTLESS*, *WARNING_ISSUED*, *ERROR_MESSAGE_ISSUED*, and *FATAL_ERROR_STOP*.

Another global variable, *error_count*, is increased by one when an *error* occurs without an interactive dialog, and it is reset to zero at the end of every paragraph.
If *error_count* reaches 100, $\TeX$ decides that there is no point in continuing further.

```c include/constants.h
#define SPOTLESS             0 // |history| value when nothing has been amiss yet
#define WARNING_ISSUED       1 // |history| value when |begin_diagnostic| has been called
#define ERROR_MESSAGE_ISSUED 2 // |history| value when |error| has been called
#define FATAL_ERROR_STOP     3 // |history| value when termination was premature
```

```c << Global variables >>+=
bool deletions_allowed; // is it safe for |error| to call |get_token|?
bool set_box_allowed;   // is it safe to do a \setbox assignment?
int history;            // has the source input been clean so far?
int error_count;        // the number of scrolled errors since the last paragraph ended
```
