# Section 510

The processing of conditionals is complete except for the following code, which is actually part of *expand*.
It comes into play when `\or`, `\else`, or `\fi` is scanned.

```c << Terminate the current conditional and skip to \fi >>=
if (cur_chr > if_limit) {
    if (if_limit == IF_CODE) {
        insert_relax(); // condition not yet evaluated
    }
    else {
        print_err("Extra ");
        print_cmd_chr(FI_OR_ELSE, cur_chr);
        help1("I'm ignoring this; it doesn't match any \\if.");
        error();
    }
}
else {
    while (cur_chr != FI_CODE) {
        pass_text(); // skip to \fi
    }
    // << Pop the condition stack >>
}
```
