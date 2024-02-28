# Section 581

When $\TeX$ wants to typeset a character that doesn't exist, the character node is not created; thus the output routine can assume that characters exist when it sees them.
The following procedure prints a warning message unless the user has suppressed it.

```c font_metric.c
void char_warning(internal_font_number f, eight_bits c) {
    if (tracing_lost_chars > 0) {
        begin_diagnostic();
        print_nl("Missing character: There is no ");
        print_strnumber(c);
        print(" in font ");
        slow_print(font_name[f]);
        print_char('!');
        end_diagnostic(false);
    }
}
```
