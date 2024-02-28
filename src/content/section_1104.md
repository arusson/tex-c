# Section 1104

The *REMOVE_ITEM* command removes a penalty, kern, or glue node if it appears at the tail of the current list, using a brute-force linear scan.
Like `\lastbox`, this command is not allowed in vertical mode (except internal vertical mode), since the current list in vertical mode is sent to the page builder.
But if we happen to be able to implement it in vertical mode, we do.

```c << Cases of |main_control| that build boxes and lists >>+=
any_mode(REMOVE_ITEM):
    delete_last();
    break;
```
