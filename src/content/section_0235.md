# Section 235

```c << Show the halfword code in |eqtb[n]| >>=
if (n < MATH_CODE_BASE) {
  if (n < LC_CODE_BASE) {
    print_esc("catcode");
    print_int(n - CAT_CODE_BASE);
  }
  else if (n < UC_CODE_BASE) {
    print_esc("lccode");
    print_int(n - LC_CODE_BASE);
  }
  else if (n < SF_CODE_BASE) {
    print_esc("uccode");
    print_int(n - UC_CODE_BASE);
  }
  else {
    print_esc("sfcode");
    print_int(n - SF_CODE_BASE);
  }
  print_char('=');
  print_int(equiv(n));
}
else {
    print_esc("mathcode");
    print_int(n - MATH_CODE_BASE);
    print_char('=');
    print_int(ho(equiv(n)));
}
```
