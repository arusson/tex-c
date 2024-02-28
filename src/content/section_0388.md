# Section 388

The parameters, if any, must be scanned before the macro is expanded.
Parameters are token lists without reference counts.
They are placed on an auxiliary stack called *pstack* while they are being scanned, since the *param_stack* may be losing entries during the matching process.
(Note that *param_stack* can't be gaining entries, since *macro_call* is the only routine that puts anything onto *param_stack*, and it is not recursive.)

```c << Global variables >>+=
pointer pstack[9]; // arguments supplied to a macro
```
