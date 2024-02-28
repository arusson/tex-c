# Section 1258

```c << Scan the font size specification >>=
name_in_progress = true; // this keeps |cur_name| from being changed
if (scan_keyword("at")) {
    // << Put the (positive) 'at' size into |s| >>
}
else if (scan_keyword("scaled")) {
    scan_int();
    s = -cur_val;
    if (cur_val <= 0 || cur_val > 32768) {
        print_err("Illegal magnification has been changed to 1000");
        help1("The magnification ratio must be between 1 and 32768.");
        int_error(cur_val);
        s = -1000;
    }
}
else {
    s = -1000;
}
name_in_progress = false;
```
