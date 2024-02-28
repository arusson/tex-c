# Section 1347

When an *EXTENSION* command occurs in *main_control*, in any mode, the *do_extension* routine is called.

```c << Cases of |main_control| that are for extensions to TeX >>=
any_mode(EXTENSION):
    do_extension();
    break;
```
