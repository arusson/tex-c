# Section 663

```c << Finish issuing a diagnostic message for an overfull or underfull hbox >>=
if (output_active) {
    print(") has occurred while \\output is active");
}
else {
    if (pack_begin_line != 0) {
        if (pack_begin_line > 0) {
            print(") in paragraph at lines ");
        }
        else {
            print(") in alignment at lines ");
        }
        print_int(abs(pack_begin_line));
        print("--");
    }
    else {
        print(") detected at line ");
    }
    print_int(line);
}
print_ln();
font_in_short_display = NULL_FONT;
short_display(list_ptr(r));
print_ln();
begin_diagnostic();
show_box(r);
end_diagnostic(true);
```
