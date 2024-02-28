# Section 1045

Whew---that covers the main loop.
We can now proceed at a leisurely pace through the other combinations of possibilities.

```c include/builder.h
// for mode-independent commands
#define any_mode(X)   \
    case VMODE + (X): \
    case HMODE + (X): \
    case MMODE + (X)
```

```c << Cases of |main_control| that are not part of the inner loop >>=
any_mode(RELAX):
case VMODE + SPACER:
case MMODE + SPACER:
case MMODE + NO_BOUNDARY:
    do_nothing;
    break;

any_mode(IGNORE_SPACES):
    // << Get the next non-blank non-call token >>
    goto reswitch;

case VMODE + STOP:
    if (its_all_over()) {
        // this is the only way out
        return;
    }
    break;

// << Forbidden cases detected in |main_control| >>
any_mode(MAC_PARAM):
    report_illegal_case();
    break;

// << Math-only cases in non-math modes, or vice versa >>
    insert_dollar_sign();
    break;

// << Cases of |main_control| that build boxes and lists >>

// << Cases of |main_control| that don't depend on |mode| >>

// << Cases of |main_control| that are for extensions to TeX >>
```
