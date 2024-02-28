// ~~~ Section 336 ~~~
// ~~~ Start file |get_next_token.c|, 1382 ~~~
#include "alignment.h"
#include "texerror.h"
#include "parser.h"
// ~~~ End section 1382 ~~~

void check_outer_validity() {
    pointer p; // points to inserted token list
    pointer q; // auxiliary pointer
    if (scanner_status != NORMAL) {
        deletions_allowed = false;
        // ~~~ Back up an outer control sequence so that it can be reread, 337 ~~~
        if (cur_cs != 0) {
            if (state == TOKEN_LIST || name < 1 || name > 17) {
                p = get_avail();
                info(p) = CS_TOKEN_FLAG + cur_cs;
                back_list(p); // prepare to read the control sequence again
            }
            cur_cmd = SPACER;
            cur_chr = ' '; // replace it by a space
        }
        // ~~~ End section 337 ~~~
        if (scanner_status > SKIPPING) {
            // ~~~ Tell the user what has run away and try to recover, 338 ~~~
            runaway(); // print a definition, argument, or preamble
            if (cur_cs == 0) {
                print_err("File ended");
            }
            else {
                cur_cs = 0;
                print_err("Forbidden control sequence found");
            }
            print(" while scanning ");
            // ~~~ Print either 'definition' or 'use' or 'preamble' or 'text', and insert tokens that should lead to recovery, 339 ~~~
            p = get_avail();
            switch (scanner_status) {
            case DEFINING:
                print("definition");
                info(p) = RIGHT_BRACE_TOKEN + '}';
                break;
            
            case MATCHING:
                print("use");
                info(p) = par_token;
                long_state = OUTER_CALL;
                break;
            
            case ALIGNING:
                print("preamble");
                info(p) = RIGHT_BRACE_TOKEN + '}';
                q = p;
                p = get_avail();
                link(p) = q;
                info(p) = CS_TOKEN_FLAG + FROZEN_CR;
                align_state = -1000000;
                break;
            
            case ABSORBING:
                print("text");
                info(p) = RIGHT_BRACE_TOKEN + '}';
            } // there are no other cases
            ins_list(p);
            // ~~~ End section 339 ~~~
            print(" of ");
            sprint_cs(warning_index);
            help4("I suspect you have forgotten a `}', causing me")
                ("to read past where you wanted me to stop.")
                ("I'll try to recover; but if the error is serious,")
                ("you'd better type `E' or `X' now and fix your file.");
            error();
            // ~~~ End section 338 ~~~
        }
        else {
            print_err("Incomplete ");
            print_cmd_chr(IF_TEST, cur_if);
            print("; all text was ignored after line ");
            print_int(skip_line);
            help3("A forbidden control sequence occurred in skipped text.")
                ("This kind of error happens when you say `\\if...' and forget")
                ("the matching `\\fi'. I've inserted a `\\fi'; this might work.");
            if (cur_cs != 0) {
                cur_cs = 0;
            }
            else {
                help_line[2] = "The file ended while I was skipping conditional text.";
            }
            cur_tok = CS_TOKEN_FLAG + FROZEN_FI;
            ins_error();
        }
        deletions_allowed = true;
    }
}
// ~~~ End section 336 ~~~

// ~~~ Section 341 ~~~
// sets |cur_cmd|, |cur_chr|, |cur_cs| to next token
void get_next() {
   // restart:  go here to get the next input token
   // switch:   go here to eat the next character from a file
   // reswitch: go here to digest it again
   // start_cs: go here to start looking for a control sequence
   // found:    go here when a control sequence has been found
   // return    go here when the next input token has been got
    int k;            // an index into |buffer|
    halfword t;       // a token
    int cat;          // |cat_code(cur_chr)|, usually
    ASCII_code c, cc; // constituents of a possible expanded code
    int d;            // number of excess characters in an expanded code
restart:
    cur_cs = 0;
    if (state != TOKEN_LIST) {
        // ~~~ Input from external file, |goto restart| if no input found, 343 ~~~
switch_lbl:
        if (loc <= limit) {
            // current line not yet finished
            cur_chr = buffer[loc];
            incr(loc);
reswitch:
            cur_cmd = cat_code(cur_chr);
            // ~~~ Change state if necessary, and |goto switch| if the current character should be ignored, or |goto reswitch| if the current character changes to another, 344 ~~~
            switch (state + cur_cmd) {
            // ~~~ Cases where character is ignored, 345 ~~~
            any_state_plus(IGNORE):
            case SKIP_BLANKS + SPACER:
            case NEW_LINE + SPACER:
            // ~~~ End section 345 ~~~
                goto switch_lbl;
            
            any_state_plus(ESCAPE):
                // ~~~ Scan a control sequence and set |state = SKIP_BLANKS| or |MID_LINE|, 354 ~~~
                if (loc > limit) {
                    // |state| is irrelevant in this case
                    cur_cs = NULL_CS;
                }
                else {
start_cs:
                    k = loc;
                    cur_chr = buffer[k];
                    cat = cat_code(cur_chr);
                    incr(k);
                    if (cat == LETTER) {
                        state = SKIP_BLANKS;
                    }
                    else if (cat == SPACER) {
                        state = SKIP_BLANKS;
                    }
                    else {
                        state = MID_LINE;
                    }
                    if (cat == LETTER && k <= limit) {
                        // ~~~ Scan ahead in the buffer until finding a nonletter; if an expanded code is encountered, reduce it and |goto start_cs|; otherwise if a multiletter control sequence is found, adjust |cur_cs| and |loc|, and |goto found|, 356 ~~~
                        do {
                            cur_chr = buffer[k];
                            cat = cat_code(cur_chr);
                            incr(k);
                        } while (cat == LETTER && k <= limit);
                        // ~~~ If an expanded code is present, reduce it and |goto start_cs|, 355 ~~~
                        if (buffer[k] == cur_chr
                            && cat == SUP_MARK
                            && k < limit)
                        {
                            c = buffer[k + 1];
                            if (c < 128) {
                                 // yes, one is indeed present
                                d = 2;
                                if (is_hex(c) && k + 2 <= limit) {
                                    cc = buffer[k + 2];
                                    if (is_hex(cc)) {
                                        incr(d);
                                    }
                                }
                                if (d > 2) {
                                    hex_to_cur_chr;
                                    buffer[k - 1] = cur_chr;
                                }
                                else if (c < 64) {
                                    buffer[k - 1] = c + 64;
                                }
                                else {
                                    buffer[k - 1] = c - 64;
                                }
                                limit -= d;
                                first -= d;
                                while (k <= limit) {
                                    buffer[k] = buffer[k + d];
                                    incr(k);
                                }
                                goto start_cs;
                            }
                        }
                        // ~~~ End section 355 ~~~
                        if (cat != LETTER) {
                            decr(k);
                        } // now |k| points to first nonletter
                        if (k > loc + 1) {
                            // multiletter control sequence has been scanned
                            cur_cs = id_lookup(loc, k - loc);
                            loc = k;
                            goto found;
                        }
                        // ~~~ End section 356 ~~~
                    }
                    else {
                        // ~~~ If an expanded code is present, reduce it and |goto start_cs|, 355 ~~~
                        if (buffer[k] == cur_chr
                            && cat == SUP_MARK
                            && k < limit)
                        {
                            c = buffer[k + 1];
                            if (c < 128) {
                                 // yes, one is indeed present
                                d = 2;
                                if (is_hex(c) && k + 2 <= limit) {
                                    cc = buffer[k + 2];
                                    if (is_hex(cc)) {
                                        incr(d);
                                    }
                                }
                                if (d > 2) {
                                    hex_to_cur_chr;
                                    buffer[k - 1] = cur_chr;
                                }
                                else if (c < 64) {
                                    buffer[k - 1] = c + 64;
                                }
                                else {
                                    buffer[k - 1] = c - 64;
                                }
                                limit -= d;
                                first -= d;
                                while (k <= limit) {
                                    buffer[k] = buffer[k + d];
                                    incr(k);
                                }
                                goto start_cs;
                            }
                        }
                        // ~~~ End section 355 ~~~
                    }
                    cur_cs = SINGLE_BASE + buffer[loc];
                    incr(loc);
                }
found:
                cur_cmd = eq_type(cur_cs);
                cur_chr = equiv(cur_cs);
                if (cur_cmd >= OUTER_CALL) {
                    check_outer_validity();
                }
                // ~~~ End section 354 ~~~
                break;
            
            any_state_plus(ACTIVE_CHAR):
                // ~~~ Process an active-character control sequence and set |state = MID_LINE|, 353 ~~~
                cur_cs = cur_chr + ACTIVE_BASE;
                cur_cmd = eq_type(cur_cs);
                cur_chr = equiv(cur_cs);
                state = MID_LINE;
                if (cur_cmd >= OUTER_CALL) {
                    check_outer_validity();
                }
                // ~~~ End section 353 ~~~
                break;
            
            any_state_plus(SUP_MARK):
                // ~~~ If this |SUP_MARK| starts an expanded character like ^^A or ^^df, then |goto reswitch|, otherwise set |state = MID_LINE|, 352 ~~~
                if (cur_chr == buffer[loc] && loc < limit) {
                    c = buffer[loc + 1];
                    if (c < 128) {
                        // yes we have an expanded char
                        loc += 2;
                        if (is_hex(c) && loc <= limit) {
                            cc = buffer[loc];
                            if (is_hex(cc)) {
                                incr(loc);
                                hex_to_cur_chr;
                                goto reswitch;
                            }
                        }
                        if (c < 64) {
                            cur_chr = c + 64;
                        }
                        else {
                            cur_chr = c - 64;
                        }
                        goto reswitch;
                    }
                }
                state = MID_LINE;
                // ~~~ End section 352 ~~~
                break;
            
            any_state_plus(INVALID_CHAR):
                // ~~~ Decry the invalid character and |goto restart|, 346 ~~~
                print_err("Text line contains an invalid character");
                help2("A funny symbol that I can't read has just been input.")
                    ("Continue, and I'll forget that it ever happened.");
                deletions_allowed = false;
                error();
                deletions_allowed = true;
                goto restart;
                // ~~~ End section 346 ~~~
            
            // ~~~ Handle situations involving spaces, braces, changes of state, 347 ~~~
            case MID_LINE + SPACER:
                // ~~~ Enter |SKIP_BLANKS| state, emit a space, 349 ~~~
                state = SKIP_BLANKS;
                cur_chr = ' ';
                // ~~~ End section 349 ~~~
                break;
            
            case MID_LINE + CAR_RET:
                // ~~~ Finish line, emit a space, 348 ~~~
                loc = limit + 1;
                cur_cmd = SPACER;
                cur_chr = ' ';
                // ~~~ End section 348 ~~~
                break;
            
            case SKIP_BLANKS + CAR_RET:
            any_state_plus(COMMENT):
                // ~~~ Finish line, |goto switch_lbl|, 350 ~~~
                loc = limit + 1;
                goto switch_lbl;
                // ~~~ End section 350 ~~~
                
            case NEW_LINE + CAR_RET:
                // ~~~ Finish line, emit a \par, 351 ~~~
                loc = limit + 1;
                cur_cs = par_loc;
                cur_cmd = eq_type(cur_cs);
                cur_chr = equiv(cur_cs);
                if (cur_cmd >= OUTER_CALL) {
                    check_outer_validity();
                }
                // ~~~ End section 351 ~~~
                break;
            
            case MID_LINE + LEFT_BRACE:
                incr(align_state);
                break;
            
            case SKIP_BLANKS + LEFT_BRACE:
            case NEW_LINE + LEFT_BRACE:
                state = MID_LINE;
                incr(align_state);
                break;
            
            case MID_LINE + RIGHT_BRACE:
                decr(align_state);
                break;
            
            case SKIP_BLANKS + RIGHT_BRACE:
            case NEW_LINE + RIGHT_BRACE:
                state = MID_LINE;
                decr(align_state);
                break;
            
            add_delims_to(SKIP_BLANKS):
            add_delims_to(NEW_LINE):
                state = MID_LINE;
                break;
            // ~~~ End section 347 ~~~
            
            default:
                do_nothing;
            }
            // ~~~ End section 344 ~~~
        }
        else {
            state = NEW_LINE;
            // ~~~ Move to next line of file, or |goto restart| if there is no next line, or |return| if a \read line has finished, 360 ~~~
            if (name > 17) {
                // ~~~ Read next line of file into |buffer|, or |goto restart| if the file has ended, 362 ~~~
                incr(line);
                first = start;
                if (!force_eof) {
                    if (input_ln(cur_file)) {
                        // not end of file
                        firm_up_the_line(); // this sets |limit|
                    }
                    else {
                        force_eof = true;
                    }
                }
                if (force_eof) {
                    print_char(')');
                    decr(open_parens);
                    update_terminal; // show user that file has been read
                    force_eof = false;
                    end_file_reading(); // resume previous level
                    check_outer_validity();
                    goto restart;
                }
                if (end_line_char_inactive) {
                    decr(limit);
                }
                else {
                    buffer[limit] = end_line_char;
                }
                first = limit + 1;
                loc = start; // ready to read
                // ~~~ End section 362 ~~~
            }
            else {
                if (!terminal_input){
                    // \read line has ended
                    cur_cmd = 0;
                    cur_chr = 0;
                    return;
                }
                if (input_ptr > 0) {
                    // text was inserted during error recovery
                    end_file_reading();
                    goto restart; // resume previous level
                }
                if (selector < LOG_ONLY) {
                    open_log_file();
                }
                if (interaction > NONSTOP_MODE) {
                    if (end_line_char_inactive) {
                        incr(limit);
                    }
                    if (limit == start) {
                        // previous line was empty
                        print_nl("(Please type a command or say `\\end')");
                    }
                    print_ln();
                    first = start;
                    prompt_input("*"); // input on-line into |buffer|
                    limit = last;
                    if (end_line_char_inactive) {
                        decr(limit);
                    }
                    else {
                        buffer[limit] = end_line_char;
                    }
                    first = limit + 1;
                    loc = start;
                }
                else {
                    // nonstop mode, which is intended for overnight batch processing, never waits for on-line input
                    fatal_error("*** (job aborted, no legal \\end found)");
                }
            }
            // ~~~ End section 360 ~~~
            check_interrupt;
            goto switch_lbl;
        }
        // ~~~ End section 343 ~~~
    }
    else {
        // ~~~ Input from token list, |goto restart| if end of list or if a parameter needs to be expanded, 357 ~~~
        if (loc != null) {
            // list not exhausted
            t = info(loc);
            loc = link(loc); // move to next
            if (t >= CS_TOKEN_FLAG) {
                // a control sequence token
                cur_cs = t - CS_TOKEN_FLAG;
                cur_cmd = eq_type(cur_cs);
                cur_chr = equiv(cur_cs);
                if (cur_cmd >= OUTER_CALL) {
                    if (cur_cmd == DONT_EXPAND) {
                        // ~~~ Get the next token, suppressing expansion, 358 ~~~
                        cur_cs = info(loc) - CS_TOKEN_FLAG;
                        loc = null;
                        cur_cmd = eq_type(cur_cs);
                        cur_chr = equiv(cur_cs);
                        if (cur_cmd > MAX_COMMAND) {
                            cur_cmd = RELAX;
                            cur_chr = NO_EXPAND_FLAG;
                        }
                        // ~~~ End section 358 ~~~
                    }
                    else {
                        check_outer_validity();
                    }
                }
            }
            else {
                cur_cmd = t / 256;
                cur_chr = t % 256;
                switch (cur_cmd) {
                case LEFT_BRACE:
                    incr(align_state);
                    break;
                
                case RIGHT_BRACE:
                    decr(align_state);
                    break;
                
                case OUT_PARAM:
                    // ~~~ Insert macro parameter and |goto restart|, 359 ~~~
                    begin_token_list(param_stack[param_start + cur_chr - 1], PARAMETER);
                    goto restart;
                    // ~~~ End section 359 ~~~
                
                default:
                    do_nothing;
                }
            }
        }
        else {
            // we are done with this token list
            end_token_list();
            goto restart; // resume previous level
        }
        // ~~~ End section 357 ~~~
    }
    // ~~~ If an alignment entry has just ended, take appropriate action, 342 ~~~
    if (cur_cmd <= CAR_RET
        && cur_cmd >= TAB_MARK
        && align_state == 0)
    {
        // ~~~ Insert the <v_j> template and |goto restart|, 789 ~~~
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
        // ~~~ End section 789 ~~~
    }
    // ~~~ End section 342 ~~~
}
// ~~~ End section 341 ~~~

// ~~~ Section 363 ~~~
void firm_up_the_line() {
    int k; // an index into |buffer|
    limit = last;
    if (pausing > 0 && interaction > NONSTOP_MODE) {
        print_ln();
        if (start < limit) {
            for(k = start; k < limit; k++) {
                print_strnumber(buffer[k]);
            }
        }
        first = limit;
        prompt_input("=>"); // wait for user response
        if (last > first) {
            for(k = first; k < last; k++) {
                // move line down in buffer
                buffer[k + start - first] = buffer[k];
            }
            limit = start + last - first;
        }
    }
}
// ~~~ End section 363 ~~~

// ~~~ Section 365 ~~~
// sets |cur_cmd|, |cur_chr|, |cur_tok|
void get_token() {
    no_new_control_sequence = false;
    get_next();
    no_new_control_sequence = true;
    if (cur_cs == 0) {
        cur_tok = (cur_cmd * 256) + cur_chr;
    }
    else {
        cur_tok = CS_TOKEN_FLAG + cur_cs;
    }
}
// ~~~ End section 365 ~~~
