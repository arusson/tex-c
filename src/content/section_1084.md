# Section 1084

```c builder/boxes_and_lists.c
// the next input should specify a box or perhaps a rule
void scan_box(int box_context) {
    // << Get the next non-blank non-relax non-call token >>
    if (cur_cmd == MAKE_BOX) {
        begin_box(box_context);
    }
    else if (box_context >= LEADER_FLAG
        && (cur_cmd == HRULE || cur_cmd == VRULE))
    {
        cur_box = scan_rule_spec();
        box_end(box_context);
    }
    else {
        print_err("A <box> was supposed to be here");
        help3("I was expecting to see \\hbox or \\vbox or \\copy or \\box or")
            ("something like that. So you might find something missing in")
            ("your output. But keep trying; you can fix this later.");
        back_error();
    }
}
```
