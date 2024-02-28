# Section 1133

```c << Cases of |handle_right_brace| where a |RIGHT_BRACE| triggers a delayed action >>+=
case NO_ALIGN_GROUP:
    end_graf();
    unsave();
    align_peek();
    break;
```
