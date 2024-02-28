# Section 333

The value of *par_loc* is the *eqtb* address of '`\par`'.
This quantity
is needed because a blank line of input is supposed to be exactly equivalent
to the appearance of `\par`; we must set *cur_cs &larr; par_loc* when detecting a blank line.

```c << Global variables >>+=
pointer par_loc;    // location of \par in eqtb
halfword par_token; // token representing \par
```
