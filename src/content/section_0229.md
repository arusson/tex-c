# Section 229

```c << Show equivalent |n|, in region 3 >>=
if (n < SKIP_BASE) {
    print_skip_param(n - GLUE_BASE);
    print_char('=');
    if (n < GLUE_BASE + THIN_MU_SKIP_CODE) {
        print_spec(equiv(n), "pt");
    }
    else {
        print_spec(equiv(n), "mu");
    }
} 
else if (n < MU_SKIP_BASE) {
  print_esc("skip");
  print_int(n - SKIP_BASE);
  print_char('=');
  print_spec(equiv(n), "pt");
}
else {
    print_esc("muskip");
    print_int(n - MU_SKIP_BASE);
    print_char('=');
    print_spec(equiv(n), "mu");
}
```
