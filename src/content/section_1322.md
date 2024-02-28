# Section 1322

```c << Dump the array info for internal font number |k| >>=
dump_qqqq(font_check[k]);
dump_int(font_size[k]);
dump_int(font_dsize[k]);
dump_int(font_params[k]);
dump_int(hyphen_char[k]);
dump_int(skew_char[k]);
dump_int(font_name[k]);
dump_int(font_area[k]);
dump_int(font_bc[k]);
dump_int(font_ec[k]);
dump_int(char_base[k]);
dump_int(width_base[k]);
dump_int(height_base[k]);
dump_int(depth_base[k]);
dump_int(italic_base[k]);
dump_int(lig_kern_base[k]);
dump_int(kern_base[k]);
dump_int(exten_base[k]);
dump_int(param_base[k]);
dump_int(font_glue[k]);
dump_int(bchar_label[k]);
dump_int(font_bchar[k]);
dump_int(font_false_bchar[k]);
print_nl("\\font");
print_esc_strnumber(font_id_text(k));
print_char('=');
print_file_name(font_name[k], font_area[k], EMPTY_STRING);
if (font_size[k] != font_dsize[k]) {
    print(" at ");
    print_scaled(font_size[k]);
    print("pt");
}
```
