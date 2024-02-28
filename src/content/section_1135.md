# Section 1135

```c << Declare action procedures for use by |main_control| >>+=
void cs_error() {
    print_err("Extra ");
    print_esc("endcsname");
    help1("I'm ignoring this, since I wasn't doing a \\csname.");
    error();
}
```
