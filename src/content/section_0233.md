# Section 233

```c << Show equivalent |n|, in region 4 >>=
if (n == PAR_SHAPE_LOC) {
    print_esc("parshape");
    print_char('=');
    if (par_shape_ptr == null) {
        print_char('0');
    }
    else {
        print_int(info(par_shape_ptr));
    }
}
else if (n < TOKS_BASE) {
  print_cmd_chr(ASSIGN_TOKS, n);
  print_char('=');
  if (equiv(n) != null) {
    show_token_list(link(equiv(n)), null, 32);
  }
}
else if (n < BOX_BASE) {
  print_esc("toks");
  print_int(n - TOKS_BASE);
  print_char('=');
  if (equiv(n) != null) {
    show_token_list(link(equiv(n)), null, 32);
  }
}
else if (n < CUR_FONT_LOC) {
  print_esc("box");
  print_int(n - BOX_BASE);
  print_char('=');
  if (equiv(n) == null) {
    print("void");
  }
  else {
    depth_threshold = 0;
    breadth_max = 1;
    show_node_list(equiv(n));
  }
}
else if (n < CAT_CODE_BASE) {
    // << Show the font identifier in |eqtb[n]| >>
}
else {
    // << Show the halfword code in |eqtb[n]| >>
}
```
