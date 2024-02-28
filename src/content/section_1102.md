# Section 1102

Penalty nodes get into a list via the *BREAK_PENALTY* command.

```c << Cases of |main_control| that build boxes and lists >>+=
any_mode(BREAK_PENALTY):
    append_penalty();
    break;
```
