# Section 1271

```c << Cases of |main_control| that don't depend on |mode| >>+=
any_mode(AFTER_GROUP):
    get_token();
    save_for_after(cur_tok);
    break;
```
