# Section 1085

When the right brace occurs at the end of an `\hbox` or `\vbox` or `\vtop` construction, the *package* routine comes into action.
We might also have to finish a paragraph that hasn't ended.

```c << Cases of |handle_right_brace| where a |RIGHT_BRACE| triggers a delayed action >>=
case HBOX_GROUP:
    package(0);
    break;

case ADJUSTED_HBOX_GROUP:
    adjust_tail = ADJUST_HEAD;
    package(0);
    break;

case VBOX_GROUP:
    end_graf();
    package(0);
    break;

case VTOP_GROUP:
    end_graf();
    package(VTOP_CODE);
    break;
```
