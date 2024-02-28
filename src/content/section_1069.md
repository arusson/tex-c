# Section 1069

```c << Declare action procedures for use by |main_control| >>+=
void extra_right_brace() {
    print_err("Extra }, or forgotten ");
    switch (cur_group) {
    case SEMI_SIMPLE_GROUP:
        print_esc("endgroup");
        break;
    
    case MATH_SHIFT_GROUP:
        print_char('$');
        break;

    case MATH_LEFT_GROUP:
        print_esc("right");
    }
    help5("I've deleted a group-closing symbol because it seems to be")
        ("spurious, as in `$x}$'. But perhaps the } is legitimate and")
        ("you forgot something else, as in `\\hbox{$x}'. In such cases")
        ("the way to recover is to insert both the forgotten and the")
        ("deleted material, e.g., by typing `I$}'.");
    error();
    incr(align_state);
}
```
