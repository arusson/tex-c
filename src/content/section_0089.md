# Section 89

```c << Print the help information and |goto continue| >>=
if (use_err_help) {
    give_err_help();
    use_err_help = false;
}
else {
    if (help_ptr == 0) {
        help2("Sorry, I don't know how to help in this situation.")
            ("Maybe you should try asking a human?");
    }
    do {
        decr(help_ptr);
        print(help_line[help_ptr]);
        print_ln();
    } while (help_ptr != 0);
}
help4("Sorry, I already gave what help I could...")
    ("Maybe you should try asking a human?")
    ("An error might have occurred before I noticed any problems.")
    ("``If all else fails, read the instructions.''");
continue;
```
