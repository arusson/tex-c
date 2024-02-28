# Section 405

The *scan_optional_equals* routine looks for an optional '`=`' sign preceded by optional spaces; '`\relax`' is not ignored here.

```c parser/subroutines.c
void scan_optional_equals() {
    // << Get the next non-blank non-call token >>
    if (cur_tok != OTHER_TOKEN + '=') {
        back_input();
    }
}
```
