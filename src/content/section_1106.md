# Section 1106

```c << Apologize for inability to do the operation now, unless \unskip follows non-glue >>=
if (cur_chr != GLUE_NODE || last_glue != MAX_HALFWORD) {
    you_cant();
    help2("Sorry...I usually can't take things from the current page.")
        ("Try `I\\vskip-\\lastskip' instead.");
    if (cur_chr == KERN_NODE) {
        help_line[0] = "Try `I\\kern-\\lastkern' instead.";
    }
    else if (cur_chr != GLUE_NODE) {
        help_line[0] = "Perhaps you can make the output routine do it.";
    }
    error();
}
```
