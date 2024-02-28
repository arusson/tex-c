# Section 361

The global variable *force_eof* is normally *false*; it is set *true* by an `\endinput` command.

```c << Global variables >>+=
bool force_eof; // should the next \input be aborted early?
```
