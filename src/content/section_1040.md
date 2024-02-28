# Section 1040

When a ligature or kern instruction matches a character, we know from *read_font_info* that the character exists in the font, even though we haven't verified its existence in the normal way.

This section could be made into a subroutine, if the code inside *main_control* needs to be shortened.

```c << Do ligature or kern command, returning to |main_lig_loop| or |main_loop_wrapup| or |main_loop_move| >>=
if (op_byte(main_j) >= KERN_FLAG) {
    wrapup(rt_hit);
    tail_append(new_kern(char_kern(main_f, main_j)));
    goto main_loop_move;
}
if (cur_l == NON_CHAR) {
    lft_hit = true;
}
else if (lig_stack == null) {
    rt_hit = true;
}
check_interrupt; // allow a way out in case there's an infinite ligature loop
switch (op_byte(main_j)) {
case 1:
case 5:
    // =:|, =:|>
    cur_l = rem_byte(main_j);
    main_i = char_info(main_f, cur_l);
    ligature_present = true;
    break;

case 2:
case 6:
    // |=:, |=:>
    cur_r = rem_byte(main_j);
    if (lig_stack == null) {
        // right boundary character is being consumed
        lig_stack = new_lig_item(cur_r);
        bchar = NON_CHAR;
    }
    else if (is_char_node(lig_stack)) {
        // |link(lig_stack) = null|
        main_p = lig_stack;
        lig_stack = new_lig_item(cur_r);
        lig_ptr(lig_stack) = main_p;
    }
    else {
        character(lig_stack) = cur_r;
    }
    break;

case 3:
    // |=:|
    cur_r = rem_byte(main_j);
    main_p = lig_stack;
    lig_stack = new_lig_item(cur_r);
    link(lig_stack) = main_p;
    break;

case 7:
case 11:
    // |=:|>, |=:|>>
    wrapup(false);
    cur_q = tail;
    cur_l = rem_byte(main_j);
    main_i = char_info(main_f, cur_l);
    ligature_present = true;
    break;

default:
    // =:
    cur_l = rem_byte(main_j);
    ligature_present = true;
    if (lig_stack == null) {
        goto main_loop_wrapup;
    }
    else {
        goto main_loop_move_1;
    }
}
if (op_byte(main_j) > 4 && op_byte(main_j) != 7) {
    goto main_loop_wrapup;
}
if (cur_l < NON_CHAR) {
    goto main_lig_loop;
}
main_k = bchar_label[main_f];
goto main_lig_loop_1;
```
