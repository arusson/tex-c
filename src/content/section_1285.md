# Section 1285

The `\uppercase` and `\lowercase` commands are implemented by building a token list and then changing the cases of the letters in it.

```c << Cases of |main_control| that don't depend on |mode| >>+=
any_mode(CASE_SHIFT):
    shift_case();
    break;
```
