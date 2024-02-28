# Section 1328

```c << Create the |format_ident|, open the format file, and inform the user that dumping has begun >>=
selector = NEW_STRING;
print(" (preloaded format=");
print_strnumber(job_name);
print_char(' ');
print_int(year);
print_char('.');
print_int(month);
print_char('.');
print_int(day);
print_char(')');
if (interaction == BATCH_MODE) {
    selector = LOG_ONLY;
}
else {
    selector = TERM_AND_LOG;
}
str_room(1);
format_ident = make_string();
pack_job_name(FORMAT_EXTENSION);
while (!w_open_out(&fmt_file)) {
    prompt_file_name("format file name", FORMAT_EXTENSION);
}
print_nl("Beginning to dump on file ");
slow_print(make_name_string());
flush_string;
print_nl("");
slow_print(format_ident);
```
