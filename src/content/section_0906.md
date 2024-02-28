# Section 906

```c << Declare the function called |reconstitute| >>=
small_number reconstitute(small_number j, small_number n, halfword bchar, halfword hchar) {
    pointer p;          // temporary register for list manipulation
    pointer t;          // a node being appended to
    memory_word q;      // character information or a lig/kern instruction
    halfword cur_rh;    // hyphen character for ligature testing
    halfword test_char; // hyphen or other character for ligature testing
    scaled w;           // amount of kerning
    font_index k;       // position of current lig/kern instruction
    
    hyphen_passed = 0;
    t = HOLD_HEAD;
    w = 0;
    link(HOLD_HEAD) = null;
    // at this point |ligature_present = lft_hit = rt_hit = false|
    // << Set up data structures with the cursor following position |j| >>
continue_lbl:
    // << If there's a ligature or kern at the cursor position, update the data structures, possibly advancing |j|; continue until the cursor moves >>
    // << Append a ligature and/or kern to the translation; |goto continue| if the stack of inserted ligatures is nonempty >>
    return j;
}
```
