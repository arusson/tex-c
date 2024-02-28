# Section 1065

At this point, *link(TEMP_HEAD) = p*, a pointer to an empty one-word node.

```c << Prepare to insert a token that matches |cur_group|, and print what it is >>=
switch (cur_group) {
case SEMI_SIMPLE_GROUP:
    info(p) = CS_TOKEN_FLAG + FROZEN_END_GROUP;
    print_esc("endgroup"); 
    break;

case MATH_SHIFT_GROUP:
    info(p) = MATH_SHIFT_TOKEN + '$';
    print_char('$');
    break;

case MATH_LEFT_GROUP:
    info(p) = CS_TOKEN_FLAG + FROZEN_RIGHT;
    link(p) = get_avail();
    p = link(p);
    info(p) = OTHER_TOKEN + '.';
    print_esc("right.");
    break;

default:
    info(p) = RIGHT_BRACE_TOKEN + '}';
    print_char('}');
}
```
