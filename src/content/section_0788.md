# Section 788

When a column begins, we assume that *cur_cmd* is either *OMIT* or else the current token should be put back into the input until the $\langle u_j\rangle$ template has been scanned.
(Note that *cur_cmd* might be *TAB_MARK* or *CAR_RET*.)
We also assume that *align_state* is approximately 1000000 at this time.
We remain in the same mode, and start the template if it is called for.

```c alignment.c
void init_col() {
    extra_info(cur_align) = cur_cmd;
    if (cur_cmd == OMIT) {
        align_state = 0;
    }
    else {
        back_input();
        begin_token_list(u_part(cur_align), U_TEMPLATE);
    } // now |align_state = 1000000|
}
```
