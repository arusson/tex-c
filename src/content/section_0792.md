# Section 792

```c << If the preamble list has been traversed, check that the row has ended >>=
if (p == null && extra_info(cur_align) < CR_CODE) {
    if (cur_loop != null) {
        // << Lengthen the preamble periodically >>
    }
    else {
        print_err("Extra alignment tab has been changed to ");
        print_esc("cr");
        help3("You have given more \\span or & marks than there were")
            ("in the preamble to the \\halign or \\valign now in progress.")
            ("So I'll assume that you meant to type \\cr instead.");
        extra_info(cur_align) = CR_CODE;
        error();
    }
}
```
