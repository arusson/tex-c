# Section 1281

If `\errmessage` occurs often in *SCROLL_MODE*, without user-defined `\errhelp`, we don't want to give a long help message each time.
So we give a verbose explanation only once.

```c << Global variables >>+=
bool long_help_seen; // has the long \errmessage help been used?
```
