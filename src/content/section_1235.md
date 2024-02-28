# Section 1235

Next we consider changes to $\TeX$'s numeric registers.

```c << Assignments >>+=
case REGISTER:
case ADVANCE:
case MULTIPLY:
case DIVIDE:
    do_register_command(a);
    break;
```
