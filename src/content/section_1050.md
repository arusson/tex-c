# Section 1050

```c << Declare action procedures for use by |main_control| >>+=
void report_illegal_case() {
    you_cant();
    help4("Sorry, but I'm not programmed to handle this case;")
        ("I'll just pretend that you didn't ask for it.")
        ("If you're in the wrong mode, you might be able to")
        ("return to the right one by typing `I}' or `I$' or `I\\par'.");
    error();
}
```
