# Section 1342

The sixteen possible `\write` streams are represented by the *write_file*
array.
The *j*th file is open if and only if *write_open[j] = true*.
The last two streams are special; *write_open[16]* represents a stream number greater than 15, while *write_open[17]* represents a negative stream number, and both of these variables are always *false*.

```c << Global variables >>+=
alpha_file write_file[16];
bool write_open[18];
```
