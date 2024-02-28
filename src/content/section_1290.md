# Section 1290

We come finally to the last pieces missing from *main_control*, namely the'`\show`' commands that are useful when debugging.

```c << Cases of |main_control| that don't depend on |mode| >>+=
any_mode(XRAY):
    show_whatever();
    break;
```
