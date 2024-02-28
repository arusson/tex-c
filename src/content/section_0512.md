# Section 512

In order to isolate the system-dependent aspects of file names, the system-independent parts of $\TeX$ are expressed in terms of three system-dependent procedures called *begin_name*, *more_name*, and *end_name*.
In essence, if the user-specified characters of the file name are $c_1\ldots c_n$, the system-independent driver program does the operations

<div align="center">

*begin_name*; *more_name($c_1$)*; $\ldots$; *more_name($c_n$)*; *end_name*.
</div>

These three procedures communicate with each other via global variables.
Afterwards the file name will appear in the string pool as three strings called *cur_name*,
*cur_area*, and *cur_ext*; the latter two are null (i.e., `""`), unless they were explicitly specified by the user.

Actually the situation is slightly more complicated, because $\TeX$ needs to know when the file name ends.
The *more_name* routine is a function (with side effects) that returns *true* on the calls *more_name*$(c_1)$, ..., *more_name*$(c_{n - 1})$.
The final call *more_name*$(c_n)$ returns *false*; or, it returns *true* and the token following $c_n$ is something like '`\hbox`' (i.e., not a character).
In other words, *more_name* is supposed to return *true* unless it is sure that the file name has been completely scanned; and *end_name* is supposed to be able to finish the assembly of *cur_name*, *cur_area*, and *cur_ext* regardless of whether *more_name*$(c_n)$ returned *true* or *false*.

```c << Global variables >>+=
str_number cur_name; // name of file just scanned
str_number cur_area; // file area just scanned, or ""
str_number cur_ext;  // file extension just scanned, or ""
```
