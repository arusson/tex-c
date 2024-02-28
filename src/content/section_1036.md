# Section 1036

```c << If the cursor is immediately followed by the right boundary, |goto reswitch|; if it's followed by an invalid character, |goto big_switch|; otherwise move the cursor one step to the right and |goto main_lig_loop| >>=
if (lig_stack == null) {
    goto reswitch;
}
cur_q = tail;
cur_l = character(lig_stack);

main_loop_move_1:
if (!is_char_node(lig_stack)) {
    goto main_loop_move_lig;
}

main_loop_move_2:
if (cur_chr < font_bc[main_f] || cur_chr > font_ec[main_f]) {
    char_warning(main_f, cur_chr);
    free_avail(lig_stack);
    goto big_switch;
}
main_i = char_info(main_f, cur_l);
if (!char_exists(main_i)) {
    char_warning(main_f, cur_chr);
    free_avail(lig_stack);
    goto big_switch;
}
link(tail) = lig_stack;
tail = lig_stack; // |main_loop_lookahead| is next
```
