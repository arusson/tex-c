# Section 507

Note that '`\ifx`' will declare two macros different if one is *long*
or *outer* and the other isn't, even though the texts of the macros are the same.

We need to reset *scanner_status*, since `\outer` control sequences are allowed, but we might be scanning a macro definition or preamble.

```c << Test if two tokens match >>=
save_scanner_status = scanner_status;
scanner_status = NORMAL;
get_next();
n = cur_cs;
p = cur_cmd;
q = cur_chr;
get_next();
if (cur_cmd != p) {
    b = false;
}
else if (cur_cmd < CALL) {
    b = (cur_chr == q);
}
else {
    // << Test if two macro texts match >>
}
scanner_status = save_scanner_status;
```
