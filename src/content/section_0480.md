# Section 480

Another way to create a token list is via the `\read` command.
The sixteen files potentially usable for reading appear in the following global variables.
The value of *read_open[n]* will be *closed* if stream number *n* has not been opened or if it has been fully read;
*JUST_OPEN* if an `\openin` but not a `\read` has been done;
and *NORMAL* if it is open and ready to read the next line.

```c include/constants.h
#define CLOSED    2 // not open, or at end of file
#define JUST_OPEN 1 // newly opened, first line not yet read
```

```c << Global variables >>+=
alpha_file read_file[16]; // used for \read
int read_open[17];        // state of read_file[n]
```
