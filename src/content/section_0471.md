# Section 471

```c << Scan the argument for command |c| >>=
switch (c) {
case NUMBER_CODE:
case ROMAN_NUMERAL_CODE:
    scan_int();
    break;

case STRING_CODE:
case MEANING_CODE:
    save_scanner_status = scanner_status;
    scanner_status = NORMAL;
    get_token();
    scanner_status = save_scanner_status;
    break;

case FONT_NAME_CODE:
    scan_font_ident();
    break;

case JOB_NAME_CODE:
    if (job_name == 0) {
        open_log_file();
    }
} // there are no other cases
```
