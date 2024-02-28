# Section 1039

Even though comparatively few characters have a lig/kern program, several of the instructions here count as part of $\TeX$'s inner loop, since a potentially long sequential search must be performed.
For example, tests with Computer Modern Roman showed that about 40 per cent of all characters actually encountered in practice had a lig/kern program, and that about four lig/kern commands were investigated for every such character.

At the beginning of this code we have *main_i = char_info(main_f, cur_l)*.

```c << If there's a ligature/kern command relevant to |cur_l| and |cur_r|, adjust the text appropriately; exit to |main_loop_wrapup| >>=
if (char_tag(main_i) != LIG_TAG ||cur_r == NON_CHAR) {
    goto main_loop_wrapup;
}
main_k = lig_kern_start(main_f, main_i);
main_j = font_info[main_k];
if (skip_byte(main_j) <= STOP_FLAG) {
    goto main_lig_loop_2;
}
main_k = lig_kern_restart(main_f, main_j);

main_lig_loop_1:
main_j = font_info[main_k];

main_lig_loop_2:
if (next_char(main_j) == cur_r && skip_byte(main_j) <= STOP_FLAG) {
    // << Do ligature or kern command, returning to |main_lig_loop| or |main_loop_wrapup| or |main_loop_move| >>
}
if (skip_byte(main_j) == 0) {
    incr(main_k);
}
else {
    if (skip_byte(main_j) >= STOP_FLAG) {
        goto main_loop_wrapup;
    }
    main_k += skip_byte(main_j) + 1;
}
goto main_lig_loop_1;
```
