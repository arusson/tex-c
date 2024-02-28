# Section 219

```c << Show the auxiliary field, |a| >>=
switch(abs(m) / (MAX_COMMAND + 1)) {
case 0:
    print_nl("prevdepth ");
    if (a.sc <= IGNORE_DEPTH) {
        print("ignored");
    }
    else {
        print_scaled(a.sc);
    }
    if (nest[p].pg_field != 0) {
        print(", prevgraf ");
        print_int(nest[p].pg_field);
        print(" line");
        if (nest[p].pg_field != 1) {
            print_char('s');
        }
    }
    break;

case 1:
    print_nl("spacefactor ");
    print_int(hh_lh(a));
    if (m > 0 && hh_rh(a) > 0) {
        print(", current language ");
        print_int(hh_rh(a));
    }
    break;

case 2:
    if (a.integer != null) {
        print("this will begin denominator of:");
        show_box(a.integer);
    }
} // there are no other cases
```
