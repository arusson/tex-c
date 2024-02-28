# Section 1118

The three discretionary lists are constructed somewhat as if they were hboxes.
A subroutine called *build_discretionary* handles the transitions.
(This is sort of fun.)

```c << Cases of |handle_right_brace| where a |RIGHT_BRACE| triggers a delayed action >>+=
case DISC_GROUP:
    build_discretionary();
    break;
```
