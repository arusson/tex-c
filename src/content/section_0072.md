# Section 72: Reporting errors

When something anomalous is detected, $\TeX$ typically does something like this:

```c
print_err("Something anomalous has been detected");
help3("This is the first line of my offer to help.")
    ("This is the second line. I'm trying to")
    ("explain the best way for you to proceed.");
error;
```
A two-line help message would be given using *help2*, etc.;
these informal helps should use simple vocabulary that complements the words used in the official error message that was printed.
(Outside the U.S.A., the help messages should preferably be translated into the local vernacular.
Each line of help is at most 60 characters long, in the present implementation, so that *MAX_PRINT_LINE* will not be exceeded.)

The *print_err* procedure supplies a '`!`' before the official message, and makes sure that the terminal is awake if a stop is going to occur.
The *error* procedure supplies a '`.`' after the official message, then it shows the location of the error; and if *interaction = ERROR_STOP_MODE*, it also enters into a dialog with the user, during which time the help message may be printed.
