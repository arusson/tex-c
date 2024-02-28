# Section 785

The tricky part about alignments is getting the templates into the scanner at the right time, and recovering control when a row or column is finished.

We usually begin a row after each `\cr` has been sensed, unless that `\cr` is followed by `\noalign` or by the right brace that terminates the alignment.
The *align_peek* routine is used to look ahead and do the right thing; it either gets a new row started, or gets a `\noalign` started, or finishes off the alignment.

```c alignment.c
void align_peek() {
restart:
    align_state = 1000000;
    // << Get the next non-blank non-call token >>
    if (cur_cmd == NO_ALIGN) {
        scan_left_brace();
        new_save_level(NO_ALIGN_GROUP);
        if (mode == -VMODE) {
            normal_paragraph();
        }
    }
    else if (cur_cmd == RIGHT_BRACE) {
        fin_align();
    }
    else if (cur_cmd == CAR_RET && cur_chr == CR_CR_CODE) {
        goto restart; // ignore \crcr
    }
    else {
        init_row(); // start a new row
        init_col(); // start a new column and replace what we peeked at
    }
}
```
