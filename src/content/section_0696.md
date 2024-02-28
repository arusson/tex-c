# Section 696

```c << Display normal noad |p| >>=
switch (type(p)) {
case ORD_NOAD:
    print_esc("mathord");
    break;

case OP_NOAD:
    print_esc("mathop");
    break;

case BIN_NOAD:
    print_esc("mathbin");
    break;

case REL_NOAD:
    print_esc("mathrel");
    break;

case OPEN_NOAD:
    print_esc("mathopen");
    break;

case CLOSE_NOAD:
    print_esc("mathclose");
    break;

case PUNCT_NOAD:
    print_esc("mathpunct");
    break;

case INNER_NOAD:
    print_esc("mathinner");
    break;

case OVER_NOAD:
    print_esc("overline");
    break;

case UNDER_NOAD:
    print_esc("underline");
    break;

case VCENTER_NOAD:
    print_esc("vcenter");
    break;

case RADICAL_NOAD:
    print_esc("radical");
    print_delimiter(left_delimiter(p));
    break;

case ACCENT_NOAD:
    print_esc("accent");
    print_fam_and_char(accent_chr(p));
    break;

case LEFT_NOAD:
    print_esc("left");
    print_delimiter(delimiter(p));
    break;

case RIGHT_NOAD:
    print_esc("right");
    print_delimiter(delimiter(p));
}
if (subtype(p) != NORMAL) {
    if (subtype(p) == LIMITS) {
        print_esc("limits");
    }
    else {
        print_esc("nolimits");
    }
}
if (type(p) < LEFT_NOAD) {
    print_subsidiary_data(nucleus(p), '.');
}
print_subsidiary_data(supscr(p), '^');
print_subsidiary_data(subscr(p), '_');
```
