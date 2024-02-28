# Section 1323

```c << Undump the array info for internal font number |k| >>=
undump_qqqq(font_check[k]);
undump_int(font_size[k]);
undump_int(font_dsize[k]);
undump(MIN_HALFWORD, MAX_HALFWORD, font_params[k]);
undump_int(hyphen_char[k]);
undump_int(skew_char[k]);
undump(0, str_ptr, font_name[k]);
undump(0, str_ptr, font_area[k]);
undump(0, 255, font_bc[k]);
undump(0, 255, font_ec[k]);
undump_int(char_base[k]);
undump_int(width_base[k]);
undump_int(height_base[k]);
undump_int(depth_base[k]);
undump_int(italic_base[k]);
undump_int(lig_kern_base[k]);
undump_int(kern_base[k]);
undump_int(exten_base[k]);
undump_int(param_base[k]);
undump(MIN_HALFWORD, lo_mem_max, font_glue[k]);
undump(0, fmem_ptr - 1, bchar_label[k]);
undump(MIN_QUARTERWORD, NON_CHAR, font_bchar[k]);
undump(MIN_QUARTERWORD, NON_CHAR, font_false_bchar[k]);
```
