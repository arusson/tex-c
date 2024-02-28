# Section 346

We go to *restart* instead of to *switch*, because *state* might equal *TOKEN_LIST* after the error has been dealt with (cf. *clear_for_error_prompt*).

```c << Decry the invalid character and |goto restart| >>=
print_err("Text line contains an invalid character");
help2("A funny symbol that I can't read has just been input.")
    ("Continue, and I'll forget that it ever happened.");
deletions_allowed = false;
error();
deletions_allowed = true;
goto restart;
```
