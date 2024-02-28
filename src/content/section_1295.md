# Section 1295

```c << Cases of |print_cmd_chr| for symbolic printing of primitives >>+=
case UNDEFINED_CS:
    print("undefined");
    break;

case CALL:
    print("macro");
    break;

case LONG_CALL:
    print_esc("long macro");
    break;

case OUTER_CALL:
    print_esc("outer macro");
    break;

case LONG_OUTER_CALL:
    print_esc("long");
    print_esc("outer macro");
    break;

case END_TEMPLATE:
    print_esc("outer endtemplate");
    break;
```
