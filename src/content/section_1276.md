# Section 1276

The user can issue messages to the terminal, regardless of the current mode.

```c << Cases of |main_control| that don't depend on |mode| >>+=
any_mode(MESSAGE):
    issue_message();
    break;
```
