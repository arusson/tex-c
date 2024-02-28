# Section 1064

We have to deal with errors in which braces and such things are not properly nested.
Sometimes the user makes an error of commission by inserting an extra symbol, but sometimes the user makes an error of omission.
$\TeX$ can't always tell one from the other, so it makes a guess and tries to avoid getting into a loop.

The *off_save* routine is called when the current group code is wrong.
It tries to insert something into the user's input that will help clean off the top level.

```c builder/boxes_and_lists.c
void off_save() {
    pointer p; // inserted token
    if (cur_group == BOTTOM_LEVEL) {
        // << Drop current token and complain that it was unmatched >>
    }
    else {
        back_input();
        p = get_avail();
        link(TEMP_HEAD) = p;
        print_err("Missing ");
        // << Prepare to insert a token that matches |cur_group|, and print what it is >>
        print(" inserted");
        ins_list(link(TEMP_HEAD));
        help5("I've inserted something that you may have forgotten.")
            ("(See the <inserted text> above.)")
            ("With luck, this will get me unwedged. But if you")
            ("really didn't forget anything, try typing `2' now; then")
            ("my insertion and my current dilemma will both disappear.");
        error();
    }
}
```
