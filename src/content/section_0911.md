# Section 911

```c << Carry out a ligature replacement, updating the cursor structure and possibly advancing |j|; |goto continue| if the cursor doesn't advance, otherwise |goto done| >>=
if (cur_l == NON_CHAR) {
    lft_hit = true;
}
if (j == n && lig_stack == null) {
    rt_hit = true;
}
check_interrupt; // allow a way out in case there's an infinite ligature loop
switch (op_byte(q)) {
case 1:
case 5:
    cur_l = rem_byte(q); // =:|, =:|>
    ligature_present = true;
    break;

case 2:
case 6:
    cur_r = rem_byte(q); // |=:, |=:>
    if (lig_stack > null) {
        character(lig_stack) = cur_r;
    }
    else {
        lig_stack = new_lig_item(cur_r);
        if (j == n) {
            bchar = NON_CHAR;
        }
        else {
            p = get_avail();
            lig_ptr(lig_stack) = p;
            character(p) = hu[j + 1];
            font(p) = hf;
        }
    }
    break;

case 3:
    cur_r = rem_byte(q); // |=:|}
    p = lig_stack;
    lig_stack = new_lig_item(cur_r);
    link(lig_stack) = p;
    break;

case 7:
case 11:
    wrap_lig(false); // |=:|>, |=:|>>
    cur_q = t;
    cur_l = rem_byte(q);
    ligature_present = true;
    break;

default:
    cur_l = rem_byte(q);
    ligature_present = true; // =:
    if (lig_stack > null) {
        pop_lig_stack;
    }
    else if (j == n) {
        goto done;
    }
    else {
        append_charnode_to_t(cur_r);
        incr(j);
        set_cur_r;
    }
}
if (op_byte(q) > 4 && op_byte(q) != 7) {
    goto done;
}
goto continue_lbl;
```
