// ~~~ Section 366 ~~~
// ~~~ Start file |expand_next_token.c|, 1382 ~~~
#include "conditional.h"
#include "texerror.h"
#include "parser.h"
// ~~~ End section 1382 ~~~

void expand() {
    halfword t;      // token that is being ``expanded after''
    pointer p, q, r; // for list manipulation
    int j;           // index into |buffer|
    int cv_backup;   // to save the global quantity |cur_val|
    small_number cvl_backup, radix_backup, co_backup; // to save |cur_val_level|, etc.
    pointer backup_backup; // to save |link(BACKUP_HEAD)|
    small_number save_scanner_status; // temporary storage of |scanner_status|
    
    cv_backup = cur_val;
    cvl_backup = cur_val_level;
    radix_backup = radix;
    co_backup = cur_order;
    backup_backup = link(BACKUP_HEAD);
    if (cur_cmd < CALL) {
        // ~~~ Expand a nonmacro, 367 ~~~
        if (tracing_commands > 1) {
            show_cur_cmd_chr();
        }
        switch (cur_cmd) {
        case TOP_BOT_MARK:
            // ~~~ Insert the appropriate mark text into the scanner, 386 ~~~
            if (cur_mark[cur_chr] != null) {
                begin_token_list(cur_mark[cur_chr], MARK_TEXT);
            }
            // ~~~ End section 386 ~~~
            break;
        
        case EXPAND_AFTER:
            // ~~~ Expand the token after the next token, 368 ~~~
            get_token();
            t = cur_tok;
            get_token();
            if (cur_cmd > MAX_COMMAND) {
                expand();
            }
            else {
                back_input();
            }
            cur_tok = t;
            back_input();
            // ~~~ End section 368 ~~~
            break;
        
        case NO_EXPAND:
            // ~~~ Suppress expansion of the next token, 369 ~~~
            save_scanner_status = scanner_status;
            scanner_status = NORMAL;
            get_token();
            scanner_status = save_scanner_status;
            t = cur_tok;
            back_input(); // now |start| and |loc| point to the backed-up token |t|
            if (t >= CS_TOKEN_FLAG) {
                p = get_avail();
                info(p) = CS_TOKEN_FLAG + FROZEN_DONT_EXPAND;
                link(p) = loc;
                start = p;
                loc = p;
            }
            // ~~~ End section 369 ~~~
            break;
        
        case CS_NAME:
            // ~~~ Manufacture a control sequence name, 372 ~~~
            r = get_avail();
            p = r; // head of the list of characters
            do {
                get_x_token();
                if (cur_cs == 0) {
                    store_new_token(cur_tok);
                }
            } while (cur_cs == 0);
            if (cur_cmd != END_CS_NAME) {
                // ~~~ Complain about missing \endcsname, 373 ~~~
                print_err("Missing ");
                print_esc("endcsname");
                print(" inserted");
                help2("The control sequence marked <to be read again> should")
                    ("not appear between \\csname and \\endcsname.");
                back_error();
                // ~~~ End section 373 ~~~
            }
            // ~~~ Look up the characters of list |r| in the hash table, and set |cur_cs|, 374 ~~~
            j = first;
            p = link(r);
            while (p != null) {
                if (j >= max_buf_stack) {
                    max_buf_stack = j + 1;
                    if (max_buf_stack == BUF_SIZE) {
                        overflow("buffer size", BUF_SIZE);
                    }
                }
                buffer[j] = info(p) % 256;
                incr(j);
                p = link(p);
            }
            if (j > first + 1) {
                no_new_control_sequence = false;
                cur_cs = id_lookup(first, j - first);
                no_new_control_sequence = true;
            }
            else if (j == first) {
                cur_cs = NULL_CS; // the list is empty
            }
            else {
                cur_cs = SINGLE_BASE + buffer[first]; // the list has length one
            }
            // ~~~ End section 374 ~~~
            flush_list(r);
            if (eq_type(cur_cs) == UNDEFINED_CS) {
                eq_define(cur_cs, RELAX, 256); // N.B.: The |save_stack| might change
            } // the control sequence will now match '\relax'
            cur_tok = cur_cs + CS_TOKEN_FLAG;
            back_input();
            // ~~~ End section 372 ~~~
            break;
        
        case CONVERT:
            conv_toks();
            break; // this procedure is discussed in Part 27 below
        
        case THE:
            ins_the_toks();
            break; // this procedure is discussed in Part 27 below
        
        case IF_TEST:
            conditional();
            break; // this procedure is discussed in Part 28 below
        
        case FI_OR_ELSE:
            // ~~~ Terminate the current conditional and skip to \fi, 510 ~~~
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
                // ~~~ Pop the condition stack, 496 ~~~
                p = cond_ptr;
                if_line = if_line_field(p);
                cur_if = subtype(p);
                if_limit = type(p);
                cond_ptr = link(p);
                free_node(p, IF_NODE_SIZE);
                // ~~~ End section 496 ~~~
            }
            // ~~~ End section 510 ~~~
            break;
        
        case INPUT:
            // ~~~ Initiate or terminate input from a file, 378 ~~~
            if (cur_chr > 0) {
                force_eof = true;
            }
            else if (name_in_progress) {
                insert_relax();
            }
            else {
                start_input();
            }
            // ~~~ End section 378 ~~~
            break;
        
        default:
            // ~~~ Complain about an undefined macro, 370 ~~~
            print_err("Undefined control sequence");
            help5("The control sequence at the end of the top line")
                ("of your error message was never \\def'ed. If you have")
                ("misspelled it (e.g., `\\hobx'), type `I' and the correct")
                ("spelling (e.g., `I\\hbox'). Otherwise just continue,")
                ("and I'll forget about whatever was undefined.");
            error();
            // ~~~ End section 370 ~~~
        }
        // ~~~ End section 367 ~~~
    }
    else if (cur_cmd < END_TEMPLATE) {
        macro_call();
    }
    else {
        // ~~~ Insert a token containing |FROZEN_ENDV|, 375 ~~~
        cur_tok = CS_TOKEN_FLAG + FROZEN_ENDV;
        back_input();
        // ~~~ End section 375 ~~~
    }
    cur_val = cv_backup;
    cur_val_level = cvl_backup;
    radix = radix_backup;
    cur_order = co_backup;
    link(BACKUP_HEAD) = backup_backup;
}
// ~~~ End section 366 ~~~

// ~~~ Section 379 ~~~
void insert_relax() {
    cur_tok = CS_TOKEN_FLAG + cur_cs;
    back_input();
    cur_tok = CS_TOKEN_FLAG + FROZEN_RELAX;
    back_input();
    token_type = INSERTED;
}
// ~~~ End section 379 ~~~

// ~~~ Section 380 ~~~
// sets |cur_cmd|, |cur_chr|, |cur_tok|, and expands macros
void get_x_token() {
    // restart:
    while(true) {
        get_next();
        if (cur_cmd <= MAX_COMMAND) {
            break; // Goto done
        }
        if (cur_cmd >= CALL) {
            if (cur_cmd < END_TEMPLATE) {
                macro_call();
            }
            else {
                cur_cs = FROZEN_ENDV;
                cur_cmd = ENDV;
                break; // Goto done; |cur_chr = NULL_LIST|
            }
        }
        else {
            expand();
        }
        // Goto restart
    }
    // done:
    if (cur_cs == 0) {
        cur_tok = (cur_cmd * 256) + cur_chr;
    }
    else {
        cur_tok = CS_TOKEN_FLAG + cur_cs;
    }
}
// ~~~ End section 380 ~~~

// ~~~ Section 381 ~~~
// |get_x_token| without the initial |get_next|
void x_token() {
    while (cur_cmd > MAX_COMMAND) {
        expand();
        get_next();
    }
    if (cur_cs == 0) {
        cur_tok = (cur_cmd * 256) + cur_chr;
    }
    else {
        cur_tok = CS_TOKEN_FLAG + cur_cs;
    }
}
// ~~~ End section 381 ~~~

// ~~~ Section 389 ~~~
// invokes a user-defined control sequence
void macro_call() {
    pointer r;                 // current node in the macro's token list
    pointer p = null;          // current node in parameter token list being built
    pointer q;                 // new node being put into the token list
    pointer s;                 // backup pointer for parameter matching
    pointer t;                 // cycle pointer for backup recovery
    pointer u, v;              // auxiliary pointers for backup recovery
    pointer rbrace_ptr = null; // one step before the last |RIGHT_BRACE| token
    small_number n;            // the number of parameters scanned
    halfword unbalance;        // unmatched left braces in current parameter
    halfword m = 0;            // the number of tokens or groups (usually)
    pointer ref_count;         // start of the token list
    small_number save_scanner_status; // |scanner_status| upon entry
    pointer save_warning_index;       // |warning_index| upon entry
    ASCII_code match_chr;             // character used in parameter
    
    save_scanner_status = scanner_status;
    save_warning_index = warning_index;
    warning_index = cur_cs;
    ref_count = cur_chr;
    r = link(ref_count);
    n = 0;
    if (tracing_macros > 0) {
        // ~~~ Show the text of the macro being expanded, 401 ~~~
        begin_diagnostic();
        print_ln();
        print_cs(warning_index);
        token_show(ref_count);
        end_diagnostic(false);
        // ~~~ End section 401 ~~~
    }
    if (info(r) != END_MATCH_TOKEN) {
        // ~~~ Scan the parameters and make |link(r)| point to the macro body; but |return| if an illegal \par is detected, 391 ~~~
        scanner_status = MATCHING;
        unbalance = 0;
        long_state = eq_type(cur_cs);
        if (long_state >= OUTER_CALL) {
            long_state -= 2;
        }
        do {
            link(TEMP_HEAD) = null;
            if (info(r) > MATCH_TOKEN + 255 || info(r) < MATCH_TOKEN) {
                s = null;
            }
            else {
                match_chr = info(r) - MATCH_TOKEN;
                s = link(r);
                r = s;
                p = TEMP_HEAD;
                m = 0;
            }
            // ~~~ Scan a parameter until its delimiter string has been found; or, if |s = null|, simply scan the delimiter string, 392 ~~~
continue_lbl:
            get_token(); // set |cur_tok| to the next token of input
            if (cur_tok == info(r)) {
                // ~~~ Advance |r|; |goto found| if the parameter delimiter has been fully matched, otherwise |goto continue_lbl|, 394 ~~~
                r = link(r);
                if (info(r) >= MATCH_TOKEN && info(r) <= END_MATCH_TOKEN) {
                    if (cur_tok < LEFT_BRACE_LIMIT) {
                        decr(align_state);
                    }
                    goto found;
                }
                else {
                    goto continue_lbl;
                }
                // ~~~ End section 394 ~~~
            }
            // ~~~ Contribute the recently matched tokens to the current parameter, and |goto continue| if a partial match is still in effect; but abort if |s = null|, 397 ~~~
            if (s != r) {
                if (s == null) {
                    // ~~~ Report an improper use of the macro and abort, 398 ~~~
                    print_err("Use of ");
                    sprint_cs(warning_index);
                    print(" doesn't match its definition");
                    help4("If you say, e.g., `\\def\\a1{...}', then you must always")
                        ("put `1' after `\\a', since control sequence names are")
                        ("made up of letters only. The macro here has not been")
                        ("followed by the required stuff, so I'm ignoring it.");
                    error();
                    goto end;
                    // ~~~ End section 398 ~~~
                }
                else {
                    t = s;
                    do {
                        store_new_token(info(t));
                        incr(m);
                        u = link(t);
                        v = s;
                        while(true) {
                            if (u == r) {
                                if (cur_tok != info(v)) {
                                    goto done;
                                }
                                else {
                                    r = link(v);
                                    goto continue_lbl;
                                }
                            }
                            if (info(u) != info(v)) {
                                goto done;
                            }
                            u = link(u);
                            v = link(v);
                        }
done:
                        t = link(t);
                    } while (t != r);
                    r = s; // at this point, no tokens are recently matched
                }
            }
            // ~~~ End section 397 ~~~
            if (cur_tok == par_token && long_state != LONG_CALL) {
                // ~~~ Report a runaway argument and abort, 396 ~~~
                if (long_state == CALL) {
                    runaway();
                    print_err("Paragraph ended before ");
                    sprint_cs(warning_index);
                    print(" was complete");
                    help3("I suspect you've forgotten a `}', causing me to apply this")
                        ("control sequence to too much text. How can we recover?")
                        ("My plan is to forget the whole thing and hope for the best.");
                    back_error();
                }
                pstack[n] = link(TEMP_HEAD);
                align_state -= unbalance;
                for(m = 0; m <= n; m++) {
                    flush_list(pstack[m]);
                }
                goto end;
                // ~~~ End section 396 ~~~
            }
            if (cur_tok < RIGHT_BRACE_LIMIT) {
                if (cur_tok < LEFT_BRACE_LIMIT) {
                    // ~~~ Contribute an entire group to the current parameter, 399 ~~~
                    unbalance = 1;
                    while(true) {
                        fast_store_new_token(cur_tok);
                        get_token();
                        if (cur_tok == par_token && long_state != LONG_CALL) {
                            // ~~~ Report a runaway argument and abort, 396 ~~~
                            if (long_state == CALL) {
                                runaway();
                                print_err("Paragraph ended before ");
                                sprint_cs(warning_index);
                                print(" was complete");
                                help3("I suspect you've forgotten a `}', causing me to apply this")
                                    ("control sequence to too much text. How can we recover?")
                                    ("My plan is to forget the whole thing and hope for the best.");
                                back_error();
                            }
                            pstack[n] = link(TEMP_HEAD);
                            align_state -= unbalance;
                            for(m = 0; m <= n; m++) {
                                flush_list(pstack[m]);
                            }
                            goto end;
                            // ~~~ End section 396 ~~~
                        }
                        if (cur_tok < RIGHT_BRACE_LIMIT) {
                            if (cur_tok < LEFT_BRACE_LIMIT) {
                                incr(unbalance);
                            }
                            else {
                                decr(unbalance);
                                if (unbalance == 0) {
                                    goto done1;
                                }
                            }
                        }
                    }
done1:
                    rbrace_ptr = p;
                    store_new_token(cur_tok);
                    // ~~~ End section 399 ~~~
                }
                else {
                    // ~~~ Report an extra right brace and |goto continue|, 395 ~~~
                    back_input();
                    print_err("Argument of ");
                    sprint_cs(warning_index);
                    print(" has an extra }");
                    help6("I've run across a `}' that doesn't seem to match anything.")
                        ("For example, `\\def\\a#1{...}' and `\\a}' would produce")
                        ("this error. If you simply proceed now, the `\\par' that")
                        ("I've just inserted will cause me to report a runaway")
                        ("argument that might be the root of the problem. But if")
                        ("your `}' was spurious, just type `2' and it will go away.");
                    incr(align_state);
                    long_state = CALL;
                    cur_tok = par_token;
                    ins_error();
                    goto continue_lbl;
                    // a white lie; the \par won't always trigger a runaway
                    // ~~~ End section 395 ~~~
                }
            }
            else {
                // ~~~ Store the current token, but |goto continue_lbl| if it is a blank space that would become an undelimited parameter, 393 ~~~
                if (cur_tok == SPACE_TOKEN
                    && info(r) <= END_MATCH_TOKEN
                    && info(r) >= MATCH_TOKEN)
                {
                    goto continue_lbl;
                }
                store_new_token(cur_tok);
                // ~~~ End section 393 ~~~
            }
            incr(m);
            if (info(r) > END_MATCH_TOKEN || info(r) < MATCH_TOKEN) {
                goto continue_lbl;
            }
found:
            if (s != null) {
                // ~~~ Tidy up the parameter just scanned, and tuck it away, 400 ~~~
                if (m == 1 && info(p) < RIGHT_BRACE_LIMIT) {
                    link(rbrace_ptr) = null;
                    free_avail(p);
                    p = link(TEMP_HEAD);
                    pstack[n] = link(p);
                    free_avail(p);
                }
                else {
                    pstack[n] = link(TEMP_HEAD);
                }
                incr(n);
                if (tracing_macros > 0) {
                    begin_diagnostic();
                    print_nl_strnumber(match_chr);
                    print_int(n);
                    print("<-");
                    show_token_list(pstack[n - 1], null, 1000);
                    end_diagnostic(false);
                }
                // ~~~ End section 400 ~~~
            }
            // ~~~ End section 392 ~~~
            // now |info(r)| is a token whose command code is either |match| or |end_match|
        } while (info(r) != END_MATCH_TOKEN);
        // ~~~ End section 391 ~~~
    }
    // ~~~ Feed the macro body and its parameters to the scanner, 390 ~~~
    while (state == TOKEN_LIST
        && loc == null
        && token_type != V_TEMPLATE)
    {
        end_token_list(); // conserve stack space
    }
    begin_token_list(ref_count, MACRO);
    name = warning_index;
    loc = link(r);
    if (n > 0) {
        if (param_ptr + n > max_param_stack) {
            max_param_stack = param_ptr + n;
            if (max_param_stack > PARAM_SIZE) {
                overflow("parameter stack size", PARAM_SIZE);
            }
        }
        for(m = 0; m < n; m++) {
            param_stack[param_ptr + m] = pstack[m];
        }
        param_ptr += n;
    }
    // ~~~ End section 390 ~~~
end:
    scanner_status = save_scanner_status;
    warning_index = save_warning_index;
}
// ~~~ End section 389 ~~~
