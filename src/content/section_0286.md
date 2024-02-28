# Section 286

Most of the parameters kept in *eqtb* can be changed freely, but there's an exception:
The magnification should not be used with two different values during any $\TeX$ job, since a single magnification is applied to entire run.
The global variable *mag_set* is set to the current magnification whenever it becomes necessary to "freeze" it at a particular value.

```c << Global variables >>+=
int mag_set; // if nonzero, this magnification should be used henceforth
```
