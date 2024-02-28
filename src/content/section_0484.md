# Section 484

Here we input on-line into the *buffer* array, prompting the user explicitly if *n* $\geq$ *0*.
The value of *n* is set negative so that additional prompts will not be given in the case of multi-line input.

```c << Input for \read from the terminal >>=
if (interaction > NONSTOP_MODE) {
    if (n < 0) {
        prompt_input("");
    }
    else {
        print_ln();
        sprint_cs(r);
        prompt_input("=");
        n = -1;
    }
}
else {
    fatal_error("*** (cannot \\read from terminal in nonstop modes)");
}
```
