# Section 1335

We get to the *final_cleanup* routine when `\end` or `\dump` has been scanned and *its_all_over*.

```c << Last-minute procedures >>+=
void final_cleanup() {
    small_number c; // 0 for \end, 1 for \dump
    c = cur_chr;
    if (c != 1) {
        new_line_char = -1;
    }
    if (job_name == 0) {
        open_log_file();
    }
    while (input_ptr > 0) {
        if (state == TOKEN_LIST) {
            end_token_list();
        }
        else {
            end_file_reading();
        }
    }
    while (open_parens > 0) {
        print(" )");
        decr(open_parens);
    }
    if (cur_level > LEVEL_ONE) {
        print_nl("(");
        print_esc("end occurred ");
        print("inside a group at level ");
        print_int(cur_level - LEVEL_ONE);
        print_char(')');
    }
    while (cond_ptr != null) {
        print_nl("(");
        print_esc("end occurred ");
        print("when ");
        print_cmd_chr(IF_TEST, cur_if);
        if (if_line != 0) {
            print(" on line ");
            print_int(if_line);
        }
        print(" was incomplete)");
        if_line = if_line_field(cond_ptr);
        cur_if = subtype(cond_ptr);
        temp_ptr = cond_ptr;
        cond_ptr = link(cond_ptr);
        free_node(temp_ptr, IF_NODE_SIZE);
    }
    if (history != SPOTLESS
        && (history == WARNING_ISSUED || interaction < ERROR_STOP_MODE)
        && selector == TERM_AND_LOG)
    {
        selector = TERM_ONLY;
        print_nl("(see the transcript file for additional information)");
        selector = TERM_AND_LOG;
    }
    if (c == 1) {
#ifdef INIT
        for(c = TOP_MARK_CODE; c <= SPLIT_BOT_MARK_CODE; c++) {
            if (cur_mark[c] != null) {
                delete_token_ref(cur_mark[c]);
            }
        }
        if (last_glue != MAX_HALFWORD) {
            delete_glue_ref(last_glue);
        }
        store_fmt_file();
        return;
#endif
        print_nl("(\\dump is performed only by INITEX)");
        return;
    }
}
```
