# Section 1265

```c << Declare subprocedures for |prefixed_command| >>+=
void new_interaction() {
    print_ln();
    interaction = cur_chr;
    // << Initialize the print |selector| based on |interaction| >>
    if (log_opened) {
        selector += 2;
    }
}
```
