# Section 733

```c << Cases for noads that can follow a |BIN_NOAD| >>=
case LEFT_NOAD:
    goto done_with_noad;

case FRACTION_NOAD:
    make_fraction(q);
    goto check_dimensions;

case OP_NOAD:
    delta = make_op(q);
    if (subtype(q) == LIMITS) {
        goto check_dimensions;
    }
    break;

case ORD_NOAD:
    make_ord(q);
    break;

case OPEN_NOAD:
case INNER_NOAD:
    do_nothing;
    break;

case RADICAL_NOAD:
    make_radical(q);
    break;

case OVER_NOAD:
    make_over(q);
    break;

case UNDER_NOAD:
    make_under(q);
    break;

case ACCENT_NOAD:
    make_math_accent(q);
    break;

case VCENTER_NOAD:
    make_vcenter(q);
    break;
```
