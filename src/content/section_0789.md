# Section 789

The scanner sets *align_state* to zero when the $\langle u_j\rangle$ template ends.
When a subsequent `\cr` or `\span` or tab mark occurs with *align_state = 0*, the scanner activates the following code, which fires up the $\langle v_j\rangle$ template.
We need to remember the *cur_chr*, which is either *CR_CR_CODE*, *CR_CODE*, *SPAN_CODE*, or a character code, depending on how the column text has ended.

This part of the program had better not be activated when the preamble to another alignment is being scanned, or when no alignment preamble is active.

```c << Insert the <v_j> template and |goto restart| >>=
if (scanner_status == ALIGNING || cur_align == null) {
    fatal_error("(interwoven alignment preambles are not allowed)");
}
cur_cmd = extra_info(cur_align);
extra_info(cur_align) = cur_chr;
if (cur_cmd == OMIT) {
    begin_token_list(OMIT_TEMPLATE, V_TEMPLATE);
}
else {
    begin_token_list(v_part(cur_align), V_TEMPLATE);
}
align_state = 1000000;
goto restart;
```
