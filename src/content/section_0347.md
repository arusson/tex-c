# Section 347

```c include/parser.h
#define add_delims_to(X)   \
    case (X) + MATH_SHIFT: \
    case (X) + TAB_MARK:   \
    case (X) + MAC_PARAM:  \
    case (X) + SUB_MARK:   \
    case (X) + LETTER:     \
    case (X) + OTHER_CHAR
```

```c << Handle situations involving spaces, braces, changes of state >>=
case MID_LINE + SPACER:
    // << Enter |SKIP_BLANKS| state, emit a space >>
    break;

case MID_LINE + CAR_RET:
    // << Finish line, emit a space >>
    break;

case SKIP_BLANKS + CAR_RET:
any_state_plus(COMMENT):
    // << Finish line, |goto switch_lbl| >>
    
case NEW_LINE + CAR_RET:
    // << Finish line, emit a \par >>
    break;

case MID_LINE + LEFT_BRACE:
    incr(align_state);
    break;

case SKIP_BLANKS + LEFT_BRACE:
case NEW_LINE + LEFT_BRACE:
    state = MID_LINE;
    incr(align_state);
    break;

case MID_LINE + RIGHT_BRACE:
    decr(align_state);
    break;

case SKIP_BLANKS + RIGHT_BRACE:
case NEW_LINE + RIGHT_BRACE:
    state = MID_LINE;
    decr(align_state);
    break;

add_delims_to(SKIP_BLANKS):
add_delims_to(NEW_LINE):
    state = MID_LINE;
    break;
```
