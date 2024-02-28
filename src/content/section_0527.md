# Section 527

The global variable *name_in_progress* is used to prevent recursive use of *scan_file_name*, since the *begin_name* and other procedures communicate via global variables.
Recursion would arise only by devious tricks like '`\input\input f`';
such attempts at sabotage must be thwarted.
Furthermore, *name_in_progress* prevents `\input` from being initiated when a font size specification is being scanned.

Another global variable, *job_name*, contains the file name that was first `\input` by the user.
This name is extended by '`.log`' and '`.dvi`' and '`.fmt`' in the names of $\TeX$'s output files.

```c << Global variables >>+=
bool name_in_progress; // is a file name being scanned?
str_number job_name;   // principal file name
bool log_opened;       // has the transcript file been opened?
```
