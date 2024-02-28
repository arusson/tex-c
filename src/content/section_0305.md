# Section 305

Users of $\TeX$ sometimes forget to balance left and right braces properly, and one of the ways $\TeX$ tries to spot such errors is by considering an input file as broken into subfiles by control sequences that are declared to be `\outer`.

A variable called *scanner_status* tells $\TeX$ whether or not to complain
when a subfile ends.
This variable has six possible values:

- *NORMAL*, means that a subfile can safely end here without incident.

- *SKIPPING*, means that a subfile can safely end here, but not a file,
  because we're reading past some conditional text that was not selected.

- *DEFINING*, means that a subfile shouldn't end now because
  a macro is being defined.

- *MATCHING*, means that a subfile shouldn't end now because
  a macro is being used and we are searching for the end of its arguments.

- *ALIGNING*, means that a subfile shouldn't end now because we are
  not finished with the preamble of an `\halign` or `\valign`.

- *ABSORBING*, means that a subfile shouldn't end now because we are
  reading a balanced token list for `\message`, `\write`, etc.

If the *scanner_status* is not *NORMAL*, the variable *warning_index* points to the *eqtb* location for the relevant control sequence name to print in an error message.

```c include/constants.h
#define SKIPPING  1 // |scanner_status| when passing conditional text
#define DEFINING  2 // |scanner_status| when reading a macro definition
#define MATCHING  3 // |scanner_status| when reading macro arguments
#define ALIGNING  4 // |scanner_status| when reading an alignment preamble
#define ABSORBING 5 // |scanner_status| when reading a balanced text
```

```c << Global variables >>+=
int scanner_status;    // can a subfile end now?
pointer warning_index; // identifier relevant to non-|NORMAL| scanner status
pointer def_ref;       // reference count of token list being defined
```
