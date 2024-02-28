# Section 1268

```c << Cases of |main_control| that don't depend on |mode| >>+=
any_mode(AFTER_ASSIGNMENT):
    get_token();
    after_token = cur_tok;
    break;
```
