# Section 752

A ligature found in a math formula does not create a *LIGATURE_NODE*, because there is no question of hyphenation afterwards; the ligature will simply be stored in an ordinary *CHAR_NODE*, after residing in an *ORD_NOAD*.

The *math_type* is converted to *MATH_TEXT_CHAR* here if we would not want to apply an italic correction to the current character unless it belongs to a math font (i.e., a font with *space = 0*).

No boundary characters enter into these ligatures.

```c << Declare math construction procedures >>+=
void make_ord(pointer q) {
    int a; // address of lig/kern instruction
    pointer p, r; // temporary registers for list manipulation
restart:
    if (math_type(subscr(q)) == EMPTY
        && math_type(supscr(q)) == EMPTY
        && math_type(nucleus(q)) == MATH_CHAR)
    {
        p = link(q);
        if (p != null
            && type(p) >= ORD_NOAD
            && type(p) <= PUNCT_NOAD
            && math_type(nucleus(p)) == MATH_CHAR
            && fam(nucleus(p)) == fam(nucleus(q)))
        {
            math_type(nucleus(q)) = MATH_TEXT_CHAR;
            fetch(nucleus(q));
            if (char_tag(cur_i) == LIG_TAG) {
                a = lig_kern_start(cur_f, cur_i);
                cur_c = character(nucleus(p));
                cur_i = font_info[a];
                if (skip_byte(cur_i) > STOP_FLAG) {
                    a = lig_kern_restart(cur_f, cur_i);
                    cur_i = font_info[a];
                }
                while(true) {
                    // << If instruction |cur_i| is a kern with |cur_c|, attach the kern after |q|; or if it is a ligature with |cur_c|, combine noads |q| and |p| appropriately; then |return| if the cursor has moved past a noad, or |goto restart| >>

                    if (skip_byte(cur_i) >= STOP_FLAG) {
                        return;
                    }
                    a += skip_byte(cur_i) + 1;
                    cur_i = font_info[a];
                }
            }
        }
    }
}
```
