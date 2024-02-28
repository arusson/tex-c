# Section 34

Sometimes it is necessary to synchronize the input/output mixture that happens on the user's terminal, and three system-dependent procedures are used for this purpose.
The first of these, *update_terminal*, is called when we want to make sure that everything we have output to the terminal so far has actually left the computer's internal buffers and been sent.
The second, *clear_terminal*, is called when we wish to cancel any input that the user may have typed ahead (since we are about to issue an unexpected error message).
The third, *wake_up_terminal*, is supposed to revive the terminal if the user has disabled it by
some instruction to the operating system.
The following macros show how these operations can be specified in Pascal-H:

> ![NOTE]
> *wake_up_terminal* is not used, and *clear_terminal* has not been considered important so it does nothing.

```c include/io.h
// << Start file |io.h| >>

#define update_terminal fflush(stdout)
#define clear_terminal do_nothing
```
