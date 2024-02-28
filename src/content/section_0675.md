# Section 675

```c << Finish issuing a diagnostic message for an overfull or underfull vbox >>=
if (output_active) {
    print(") has occurred while \\output is active");
}
else {
    if (pack_begin_line != 0) {
        // it's actually negative
        print(") in alignment at lines ");
        print_int(abs(pack_begin_line));
        print("--");
    }
    else {
        print(") detected at line ");
    }
    print_int(line);
    print_ln();
}
begin_diagnostic();
show_box(r);
end_diagnostic(true);
```
