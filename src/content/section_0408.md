# Section 408

Here is a procedure that sounds an alarm when mu and non-mu units are being switched.

```c error.c
void mu_error() {
    print_err("Incompatible glue units");
    help1("I'm going to assume that 1mu=1pt when they're mixed.");
    error();
}
```
