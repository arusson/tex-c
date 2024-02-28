# Section 1034

We leave the *space_factor* unchanged if *sf_code(cur_chr) = 0*;
otherwise we set it equal to *sf_code(cur_chr)*, except that it should never change from a value less than 1000 to a value exceeding 1000.
The most common case is *sf_code(cur_chr) = 1000*, so we want that case to be fast.

The overall structure of the main loop is presented here.
Some program labels are inside the individual sections.

```c include/builder.h
#define adjust_space_factor             \
    do {                                \
        main_s = sf_code(cur_chr);      \
        if (main_s == 1000) {           \
            space_factor = 1000;        \
        }                               \
        else if (main_s < 1000) {       \
            if (main_s > 0) {           \
                space_factor = main_s;  \
            }                           \
        }                               \
        else if (space_factor < 1000) { \
            space_factor = 1000;        \
        }                               \
        else {                          \
            space_factor = main_s;      \
        }                               \
    } while (0)
```

```c << Append character |cur_chr| and the following characters (if any) to the current hlist in the current font; |goto reswitch| when a non-character has been fetched >>=
adjust_space_factor;
main_f = cur_font;
bchar = font_bchar[main_f];
false_bchar = font_false_bchar[main_f];
if (mode > 0 && language != clang) {
    fix_language();
}
fast_get_avail(lig_stack);
font(lig_stack) = main_f;
cur_l = cur_chr;
character(lig_stack) = cur_l;
cur_q = tail;
if (cancel_boundary) {
    cancel_boundary = false;
    main_k = NON_ADDRESS;
}
else {
    main_k = bchar_label[main_f];
}
if (main_k == NON_ADDRESS) {
    goto main_loop_move_2; // no left boundary processing
}
cur_r = cur_l;
cur_l = NON_CHAR;
goto main_lig_loop_1; // begin with cursor after left boundary

main_loop_wrapup:
// << Make a ligature node, if |ligature_present|; insert a null discretionary, if appropriate >>

main_loop_move:
// << If the cursor is immediately followed by the right boundary, |goto reswitch|; if it's followed by an invalid character, |goto big_switch|; otherwise move the cursor one step to the right and |goto main_lig_loop| >>

main_loop_lookahead:
// << Look ahead for another character, or leave |lig_stack| empty if there's none there >>

main_lig_loop:
// << If there's a ligature/kern command relevant to |cur_l| and |cur_r|, adjust the text appropriately; exit to |main_loop_wrapup| >>

main_loop_move_lig:
// << Move the cursor past a pseudo-ligature, then |goto main_loop_lookahead| or |main_lig_loop| >>
```
