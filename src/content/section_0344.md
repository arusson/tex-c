# Section 344

The following 48-way switch accomplishes the scanning quickly, assuming that a decent Pascal compiler has translated the code.
Note that the numeric values for *MID_LINE*, *SKIP_BLANKS*, and *NEW_LINE* are spaced apart from each other by *MAX_CHAR_CODE + 1*, so we can add a character's command code to the state to get a single number that characterizes both.

```c include/parser.h
// << Start file |parser.h| >>

#define any_state_plus(X)   \
    case MID_LINE + (X):    \
    case SKIP_BLANKS + (X): \
    case NEW_LINE + (X)
```

```c << Change state if necessary, and |goto switch| if the current character should be ignored, or |goto reswitch| if the current character changes to another >>=
switch (state + cur_cmd) {
// << Cases where character is ignored >>
    goto switch_lbl;

any_state_plus(ESCAPE):
    // << Scan a control sequence and set |state = SKIP_BLANKS| or |MID_LINE| >>
    break;

any_state_plus(ACTIVE_CHAR):
    // << Process an active-character control sequence and set |state = MID_LINE| >>
    break;

any_state_plus(SUP_MARK):
    // << If this |SUP_MARK| starts an expanded character like ^^A or ^^df, then |goto reswitch|, otherwise set |state = MID_LINE| >>
    break;

any_state_plus(INVALID_CHAR):
    // << Decry the invalid character and |goto restart| >>

// << Handle situations involving spaces, braces, changes of state >>

default:
    do_nothing;
}
```
