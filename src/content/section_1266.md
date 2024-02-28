# Section 1266

The `\afterassignment` command puts a token into the global variable *after_token*.
This global variable is examined just after every assignment has been performed.

```c << Global variables >>+=
halfword after_token; // zero, or a saved token
```
