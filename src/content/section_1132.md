# Section 1132

```c << Cases of |handle_right_brace| where a |RIGHT_BRACE| triggers a delayed action >>+=
case ALIGN_GROUP:
    back_input();
    cur_tok = CS_TOKEN_FLAG + FROZEN_CR;
    print_err("Missing ");
    print_esc("cr");
    print(" inserted");
    help1("I'm guessing that you meant to end an alignment here.");
    ins_error();
    break;
```
