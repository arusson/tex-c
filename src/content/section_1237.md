# Section 1237

Here we use the fact that the consecutive codes *INT_VAL .. MU_VAL* and *ASSIGN_INT .. ASSIGN_MU_GLUE* correspond to each other nicely.

```c << Compute the register location |l| and its type |p|; but |return| if invalid >>=
if (q != REGISTER) {
    get_x_token();
    if (cur_cmd >= ASSIGN_INT && cur_cmd <= ASSIGN_MU_GLUE) {
        l = cur_chr;
        p = cur_cmd - ASSIGN_INT;
        goto found;
    }
    if (cur_cmd != REGISTER) {
        print_err("You can't use `");
        print_cmd_chr(cur_cmd, cur_chr);
        print("' after ");
        print_cmd_chr(q, 0);
        help1("I'm forgetting what you said and not changing anything.");
        error();
        return;
    }
}
p = cur_chr;
scan_eight_bit_int();
switch (p) {
case INT_VAL:
    l = cur_val + COUNT_BASE;
    break;

case DIMEN_VAL:
    l = cur_val + SCALED_BASE;
    break;

case GLUE_VAL:
    l = cur_val + SKIP_BASE;
    break;

case MU_VAL:
    l = cur_val + MU_SKIP_BASE;
} // there are no other cases
found:
```
