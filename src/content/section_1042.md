# Section 1042

Having *font_glue* allocated for each text font saves both time and memory.
If any of the three spacing parameters are subsequently changed by the use of `\fontdimen`, the *find_font_dimen* procedure deallocates the *font_glue* specification allocated here.

```c << Find the glue specification, |main_p|, for text spaces in the current font >>=
main_p = font_glue[cur_font];
if (main_p == null) {
    main_p = new_spec(ZERO_GLUE);
    main_k = param_base[cur_font] + SPACE_CODE;
    width(main_p) = font_info[main_k].sc;       // that's |space(cur_font)|
    stretch(main_p) = font_info[main_k + 1].sc; // and |space_stretch(cur_font)|
    shrink(main_p) = font_info[main_k + 2].sc;  // and |space_shrink(cur_font)|
    font_glue[cur_font] = main_p;
}
```
