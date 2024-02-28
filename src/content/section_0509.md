# Section 509

```c << Select the appropriate case and |return| or |goto common_ending| >>=
scan_int();
n = cur_val; // |n| is the number of cases to pass
if (tracing_commands > 1) {
    begin_diagnostic();
    print("{case ");
    print_int(n);
    print_char('}');
    end_diagnostic(false);
}
while (n != 0) {
    pass_text();
    if (cond_ptr == save_cond_ptr) {
        if (cur_chr == OR_CODE) {
            decr(n);
        }
        else {
            goto common_ending;
        }
    }
    else if (cur_chr == FI_CODE) {
        // << Pop the condition stack >>
    }
}
change_if_limit(OR_CODE, save_cond_ptr);
return; // wait for \or, \else, or \fi
```
