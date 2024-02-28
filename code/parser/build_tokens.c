// ~~~ Section 464 ~~~
// ~~~ Start file |build_tokens.c|, 1382 ~~~
#include "datastructures.h"
#include "texerror.h"
#include "parser.h"
// ~~~ End section 1382 ~~~

// converts |str_pool[b .. pool_ptr - 1]| to a token list
pointer str_toks(pool_pointer b) {
    pointer p;      // tail of the token list
    pointer q;      // new node being added to the token list via |store_new_token|
    halfword t;     // token being appended
    pool_pointer k; // index into |str_pool|
    str_room(1);
    p = TEMP_HEAD;
    link(p) = null;
    k = b;
    while (k < pool_ptr) {
        t = str_pool[k];
        if (t == ' ') {
            t = SPACE_TOKEN;
        }
        else {
            t = OTHER_TOKEN + t;
        }
        fast_store_new_token(t);
        incr(k);
    }
    pool_ptr = b;
    return p;
}
// ~~~ End section 464 ~~~

// ~~~ Section 465 ~~~
pointer the_toks() {
    int  old_setting; // holds |selector| setting
    pointer p, q, r; // used for copying a token list
    pool_pointer b;  // base of temporary string
    get_x_token();
    scan_something_internal(TOK_VAL, false);
    if (cur_val_level >= IDENT_VAL) {
        // ~~~ Copy the token list, 466 ~~~
        p = TEMP_HEAD;
        link(p) = null;
        if (cur_val_level == IDENT_VAL) {
            store_new_token(CS_TOKEN_FLAG + cur_val);
        }
        else if (cur_val != null) {
            r = link(cur_val); // do not copy the reference count
            while (r != null) {
                fast_store_new_token(info(r));
                r = link(r);
            }
        }
        return p;
        // ~~~ End section 466 ~~~
    }
    else {
        old_setting = selector;
        selector = NEW_STRING;
        b = pool_ptr;
        switch (cur_val_level) {
        case INT_VAL:
            print_int(cur_val);
            break;
        
        case DIMEN_VAL:
            print_scaled(cur_val);
            print("pt");
            break;
        
        case GLUE_VAL:
            print_spec(cur_val, "pt");
            delete_glue_ref(cur_val);
            break;
        
        case MU_VAL:
            print_spec(cur_val, "mu");
            delete_glue_ref(cur_val);
        } // there are no other cases
        selector = old_setting;
        return str_toks(b);
    }
}
// ~~~ End section 465 ~~~

// ~~~ Section 467 ~~~
void ins_the_toks() {
    link(GARBAGE) = the_toks();
    ins_list(link(TEMP_HEAD));
}
// ~~~ End section 467 ~~~

// ~~~ Section 470 ~~~
void conv_toks() {
    int old_setting; // holds |selector| setting
    int c; // desired type of conversion
    small_number save_scanner_status; // |scanner_status| upon entry
    pool_pointer b; // base of temporary string
    c = cur_chr;
    // ~~~ Scan the argument for command |c|, 471 ~~~
    switch (c) {
    case NUMBER_CODE:
    case ROMAN_NUMERAL_CODE:
        scan_int();
        break;
    
    case STRING_CODE:
    case MEANING_CODE:
        save_scanner_status = scanner_status;
        scanner_status = NORMAL;
        get_token();
        scanner_status = save_scanner_status;
        break;
    
    case FONT_NAME_CODE:
        scan_font_ident();
        break;
    
    case JOB_NAME_CODE:
        if (job_name == 0) {
            open_log_file();
        }
    } // there are no other cases
    // ~~~ End section 471 ~~~
    old_setting = selector;
    selector = NEW_STRING;
    b = pool_ptr;
    // ~~~ Print the result of command |c|, 472 ~~~
    switch (c) {
    case NUMBER_CODE:
        print_int(cur_val);
        break;
    
    case ROMAN_NUMERAL_CODE:
        print_roman_int(cur_val);
        break;
    
    case STRING_CODE:
        if (cur_cs != 0) {
            sprint_cs(cur_cs);
        }
        else {
            print_char(cur_chr);
        }
        break;
    
    case MEANING_CODE:
        print_meaning();
        break;
    
    case FONT_NAME_CODE:
        print_strnumber(font_name[cur_val]);
        if (font_size[cur_val] != font_dsize[cur_val]) {
            print(" at ");
            print_scaled(font_size[cur_val]);
            print("pt");
        }
        break;
    
    case JOB_NAME_CODE:
        print_strnumber(job_name);
    } // there are no other cases
    // ~~~ End section 472 ~~~
    selector = old_setting;
    link(GARBAGE) = str_toks(b);
    ins_list(link(TEMP_HEAD));
}
// ~~~ End section 470 ~~~

// ~~~ Section 473 ~~~
pointer scan_toks(bool macro_def, bool xpand) {
    halfword t;          // token representing the highest parameter number
    halfword s;          // saved token
    pointer p;           // tail of the token list being built
    pointer q;           // new node being added to the token list via |store_new_token|
    halfword unbalance;  // number of unmatched left braces
    halfword hash_brace; // possible '#{' token
    if (macro_def) {
        scanner_status = DEFINING;
    }
    else {
        scanner_status = ABSORBING;
    }
    warning_index = cur_cs;
    def_ref = get_avail();
    token_ref_count(def_ref) = null;
    p = def_ref;
    hash_brace = 0;
    t = ZERO_TOKEN;
    if (macro_def) {
        // ~~~ Scan and build the parameter part of the macro definition, 474 ~~~
        while(true) {
            get_token(); // set |cur_cmd|, |cur_chr|, |cur_tok|
            if (cur_tok < RIGHT_BRACE_LIMIT) {
                break; // Goto done1
            }
            if (cur_cmd == MAC_PARAM) {
                // ~~~ If the next character is a parameter number, make |cur_tok| a |MATCH| token; but if it is a left brace; store '|LEFT_BRACE|, |END_MATCH|', set |hash_brace|, and |goto done|, 476 ~~~
                s = MATCH_TOKEN + cur_chr;
                get_token();
                if (cur_tok < LEFT_BRACE_LIMIT) {
                    hash_brace = cur_tok;
                    store_new_token(cur_tok);
                    store_new_token(END_MATCH_TOKEN);
                    goto done;
                }
                if (t == ZERO_TOKEN + 9) {
                    print_err("You already have nine parameters");
                    help2("I'm going to ignore the # sign you just used,")
                        ("as well as the token that followed it.");
                    error();
                    continue;
                }
                else {
                    incr(t);
                    if (cur_tok != t) {
                        print_err("Parameters must be numbered consecutively");
                        help2("I've inserted the digit you should have used after the #.")
                            ("Type `1' to delete what you did use.");
                        back_error();
                    }
                    cur_tok = s;
                }
                // ~~~ End section 476 ~~~
            }
            store_new_token(cur_tok);
        }
        // done1:
        store_new_token(END_MATCH_TOKEN);
        if (cur_cmd == RIGHT_BRACE) {
            // ~~~ Express shock at the missing left brace; |goto found|, 475 ~~~
            print_err("Missing { inserted");
            incr(align_state);
            help2("Where was the left brace? You said something like `\\def\\a}',")
                ("which I'm going to interpret as `\\def\\a{}'.");
            error();
            goto found;
            // ~~~ End section 475 ~~~
        }
done:
        // ~~~ End section 474 ~~~
    }
    else {
        scan_left_brace(); // remove the compulsory left brace
    }
    // ~~~ Scan and build the body of the token list; |goto found| when finished, 477 ~~~
    unbalance = 1;
    while(true) {
        if (xpand) {
            // ~~~ Expand the next part of the input, 478 ~~~
            while(true) {
                get_next();
                if (cur_cmd <= MAX_COMMAND) {
                    break; // Goto done2
                }
                if (cur_cmd != THE) {
                    expand();
                }
                else {
                    q = the_toks();
                    if (link(TEMP_HEAD) != null) {
                        link(p) = link(TEMP_HEAD);
                        p = q;
                    }
                }
            }
            // done2:
            x_token();
            // ~~~ End section 478 ~~~
        }
        else {
            get_token();
        }
        if (cur_tok < RIGHT_BRACE_LIMIT) {
            if (cur_cmd < RIGHT_BRACE) {
                incr(unbalance);
            }
            else {
                decr(unbalance);
                if (unbalance == 0) {
                    goto found;
                }
            }
        }
        else if (cur_cmd == MAC_PARAM && macro_def) {
            // ~~~ Look for parameter number or ##, 479 ~~~
            s = cur_tok;
            if (xpand) {
                get_x_token();
            }
            else {
                get_token();
            }
            if (cur_cmd != MAC_PARAM) {
                if (cur_tok <= ZERO_TOKEN || cur_tok > t) {
                    print_err("Illegal parameter number in definition of ");
                    sprint_cs(warning_index);
                    help3("You meant to type ## instead of #, right?")
                        ("Or maybe a } was forgotten somewhere earlier, and things")
                        ("are all screwed up? I'm going to assume that you meant ##.");
                    back_error();
                    cur_tok = s;
                }
                else {
                    cur_tok = OUT_PARAM_TOKEN - '0' + cur_chr;
                }
            }
            // ~~~ End section 479 ~~~
        }
        store_new_token(cur_tok);
    }
    // ~~~ End section 477 ~~~
found:
    scanner_status = NORMAL;
    if (hash_brace != 0) {
        store_new_token(hash_brace);
    }
    return p;
}
// ~~~ End section 473 ~~~

// ~~~ Section 482 ~~~
void read_toks(int n, pointer r) {
    pointer p;      // tail of the token list
    pointer q;      // new node being added to the token list via |store_new_token|
    int s;          // saved value of |align_state|
    small_number m; // stream number
    scanner_status = DEFINING;
    warning_index = r;
    def_ref = get_avail();
    token_ref_count(def_ref) = null;
    p = def_ref; // the reference count
    store_new_token(END_MATCH_TOKEN);
    if (n < 0 || n > 15) {
        m = 16;
    }
    else {
        m = n;
    }
    s = align_state;
    align_state = 1000000; // disable tab marks, etc.
    do {
        // ~~~ Input and store tokens from the next line of the file, 483 ~~~
        begin_file_reading();
        name = m + 1;
        if (read_open[m] == CLOSED) {
            // ~~~ Input for \read from the terminal, 484 ~~~
            if (interaction > NONSTOP_MODE) {
                if (n < 0) {
                    prompt_input("");
                }
                else {
                    print_ln();
                    sprint_cs(r);
                    prompt_input("=");
                    n = -1;
                }
            }
            else {
                fatal_error("*** (cannot \\read from terminal in nonstop modes)");
            }
            // ~~~ End section 484 ~~~
        }
        else if (read_open[m] == JUST_OPEN) {
            // ~~~ Input the first line of |read_file[m]|, 485 ~~~
            if (input_ln(read_file[m])) {
                read_open[m] = NORMAL;
            }
            else {
                a_close(read_file[m]);
                read_open[m] = CLOSED;
            }
            // ~~~ End section 485 ~~~
        }
        else {
            // ~~~ Input the next line of |read_file[m]|, 486 ~~~
            if (!input_ln(read_file[m])) {
                a_close(read_file[m]);
                read_open[m] = CLOSED;
                if (align_state != 1000000) {
                    runaway();
                    print_err("File ended within ");
                    print_esc("read");
                    help1("This \\read has unbalanced braces.");
                    align_state = 1000000;
                    limit = 0;
                    error();
                }
            }
            // ~~~ End section 486 ~~~
        }
        limit = last;
        if (end_line_char_inactive) {
            decr(limit);
        }
        else {
            buffer[limit] = end_line_char;
        }
        first = limit + 1;
        loc = start;
        state = NEW_LINE;
        while(true) {
            get_token();
            if (cur_tok == 0) {
                break; // Goto done
                // |cur_cmd == cur_chr == 0| will occur at the end of the line
            } 
            if (align_state < 1000000) {
                // unmatched '}' aborts the line
                do {
                    get_token();
                } while (cur_tok != 0);
                align_state = 1000000;
                break; // Goto done
            }
            store_new_token(cur_tok);
        }
        // done:
        end_file_reading();
        // ~~~ End section 483 ~~~
    } while (align_state != 1000000);
    cur_val = def_ref;
    scanner_status = NORMAL;
    align_state = s;
}
// ~~~ End section 482 ~~~
