# Section 1134

Finally, `\endcsname` is not supposed to get through to *main_control*.

```c << Cases of |main_control| that build boxes and lists >>+=
any_mode(END_CS_NAME):
    cs_error();
    break;
```
