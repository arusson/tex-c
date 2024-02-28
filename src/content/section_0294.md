# Section 294

The procedure usually "learns" the character code used for macro parameters by seeing one in a *MATCH* command before it runs into any *OUT_PARAM* commands.

```c << Display the token (|m|, |c|) >>=
switch(m) {
case LEFT_BRACE:
case RIGHT_BRACE:
case MATH_SHIFT:
case TAB_MARK:
case SUP_MARK:
case SUB_MARK:
case SPACER:
case LETTER:
case OTHER_CHAR:
    print_strnumber(c);
    break;

case MAC_PARAM:
    print_strnumber(c);
    print_strnumber(c);
    break;

case OUT_PARAM:
    print_strnumber(match_chr);
    if (c <= 9) {
        print_char(c + '0');
    }
    else {
        print_char('!');
        return;
    }
    break;

case MATCH:
    match_chr = c;
    print_strnumber(c);
    incr(n);
    print_char(n);
    if (n > '9') {
        return;
    }
    break;

case END_MATCH:
    print("->");
    break;

default:
    print_esc("BAD.");
}
```
