# Section 500

```c << Skip to \else or \fi, then |goto common_ending| >>=
while(true){
    pass_text();
    if (cond_ptr == save_cond_ptr) {
        if (cur_chr != OR_CODE) {
            goto common_ending;
        }
        print_err("Extra ");
        print_esc("or");
        help1("I'm ignoring this; it doesn't match any \\if.");
        error();
    }
    else if (cur_chr == FI_CODE) {
        // << Pop the condition stack >>
    }
}
```
