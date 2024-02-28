// ~~~ Section 274 ~~~
// ~~~ Start file |stack.c|, 1382 ~~~
#include "datastructures.h"
#include "texerror.h"
// ~~~ End section 1382 ~~~

// begin a new level of grouping
void new_save_level(int c) {
    check_full_save_stack;
    save_type(save_ptr) = LEVEL_BOUNDARY;
    save_level(save_ptr) = cur_group;
    save_index(save_ptr) = cur_boundary;
    if (cur_level == MAX_QUARTERWORD) {
        overflow("grouping levels", MAX_QUARTERWORD - MIN_QUARTERWORD);
    } // quit if |(cur_level + 1)| is too big to be stored in |eqtb|
    cur_boundary = save_ptr;
    incr(cur_level);
    incr(save_ptr);
    cur_group = c;
}
// ~~~ End section 274 ~~~

// ~~~ Section 275 ~~~
// gets ready to forget |w|
void eq_destroy(memory_word w) {
    pointer q; // |equiv| field of |w|
    switch(eq_type_field(w)) {
    case CALL:
    case LONG_CALL:
    case OUTER_CALL:
    case LONG_OUTER_CALL:
        delete_token_ref(equiv_field(w));
        break;

    case GLUE_REF:
        delete_glue_ref(equiv_field(w));
        break;

    case SHAPE_REF:
        q = equiv_field(w); // we need to free a \parshape block
        if (q != null) {
            // such a block is |2n+1| words long, where |n=info(q)|
            free_node(q, info(q) + info(q) + 1);
        }
        break;
    
    case BOX_REF:
        flush_node_list(equiv_field(w));
        break;
    
    default:
        do_nothing;
    }
}
// ~~~ End section 275 ~~~

// ~~~ Section 276 ~~~
// saves |eqtb[p]|
void eq_save(pointer p, quarterword l) {
    check_full_save_stack;
    if (l == LEVEL_ZERO) {
        save_type(save_ptr) = RESTORE_ZERO;
    }
    else {
        save_stack[save_ptr] = eqtb[p];
        incr(save_ptr);
        save_type(save_ptr) = RESTORE_OLD_VALUE;
    }
    save_level(save_ptr) = l;
    save_index(save_ptr) = p;
    incr(save_ptr);
}
// ~~~ End section 276 ~~~

// ~~~ Section 277 ~~~
//  new data for |eqtb|
void eq_define(pointer p, quarterword t, halfword e) {
    if (eq_level(p) == cur_level) {
        eq_destroy(eqtb[p]);
    }
    else if (cur_level > LEVEL_ONE) {
        eq_save(p, eq_level(p));
    }
    eq_level(p) = cur_level;
    eq_type(p) = t;
    equiv(p) = e;
}
// ~~~ End section 277 ~~~

// ~~~ Section 278 ~~~
void eq_word_define(pointer p, int w) {
    if (xeq_level[p] != cur_level) {
        eq_save(p, xeq_level[p]);
        xeq_level[p] = cur_level;
    }
    eqtb[p].integer = w;
}
// ~~~ End section 278 ~~~

// ~~~ Section 279 ~~~
// global |eq_define|
void geq_define(pointer p, quarterword t, halfword e) {
    eq_destroy(eqtb[p]);
    eq_level(p) = LEVEL_ONE;
    eq_type(p) = t;
    equiv(p) = e;
}

// global |eq_word_define|
void geq_word_define(pointer p, int w) {
    eqtb[p].integer = w;
    xeq_level[p] = LEVEL_ONE;
}
// ~~~ End section 279 ~~~

// ~~~ Section 280 ~~~
void save_for_after(halfword t) {
    if (cur_level > LEVEL_ONE) {
        check_full_save_stack;
        save_type(save_ptr) = INSERT_TOKEN;
        save_level(save_ptr) = LEVEL_ZERO;
        save_index(save_ptr) = t;
        incr(save_ptr);
    }
}
// ~~~ End section 280 ~~~

// ~~~ Section 281 ~~~
// ~~~ Declare the procedure called |restore_trace|, 284 ~~~
#ifdef STAT
// |eqtb[p]| has just been restored or retained
void restore_trace(pointer p, char *s) {
    begin_diagnostic();
    print_char('{');
    print(s);
    print_char(' ');
    show_eqtb(p);
    print_char('}');
    end_diagnostic(false);
}
#endif
// ~~~ End section 284 ~~~

// pops the top level off the save stack
void unsave() {
    pointer p;         // position to be restored
    quarterword l = 0; // saved level, if in fullword regions of |eqtb|
    halfword t;        // saved value of |cur_tok|
    if (cur_level > LEVEL_ONE) {
        decr(cur_level);
        // ~~~ Clear off top level from |save_stack|, 282 ~~~
        while(true) {
            decr(save_ptr);
            if (save_type(save_ptr) == LEVEL_BOUNDARY) {
                break; // Goto done
            }
            p = save_index(save_ptr);
            if (save_type(save_ptr) == INSERT_TOKEN) {
                // ~~~ Insert token |p| into TeX's input, 326 ~~~
                t = cur_tok;
                cur_tok = p;
                back_input();
                cur_tok = t;
                // ~~~ End section 326 ~~~
            }
            else {
                if (save_type(save_ptr) == RESTORE_OLD_VALUE) {
                    l = save_level(save_ptr);
                    decr(save_ptr);
                }
                else {
                    save_stack[save_ptr] = eqtb[UNDEFINED_CONTROL_SEQUENCE];
                }
                // ~~~ Store |save_stack[save_ptr]| in |eqtb[p]|, unless |eqtb[p]| holds a global value, 283 ~~~
                if (p < INT_BASE) {
                    if (eq_level(p) == LEVEL_ONE) {
                        eq_destroy(save_stack[save_ptr]); // destroy the saved value
#ifdef STAT
                        if (tracing_restores > 0) {
                            restore_trace(p, "retaining");
                        }
#endif
                    }
                    else {
                        eq_destroy(eqtb[p]); // destroy the current value
                        eqtb[p] = save_stack[save_ptr]; // restore the saved value
#ifdef STAT
                        if (tracing_restores > 0) {
                            restore_trace(p, "restoring");
                        }
#endif
                    }
                }
                else if (xeq_level[p] != LEVEL_ONE) {
                    eqtb[p] = save_stack[save_ptr];
                    xeq_level[p] = l;
#ifdef STAT
                    if (tracing_restores > 0) {
                        restore_trace(p, "restoring");
                    }
#endif
                }
#ifdef STAT
                else {
                  if (tracing_restores > 0) {
                    restore_trace(p, "retaining");
                  }
                }
#endif
                // ~~~ End section 283 ~~~
            }
        }
        // done:
        cur_group = save_level(save_ptr);
        cur_boundary = save_index(save_ptr);
        // ~~~ End section 282 ~~~
    }
    else {
        // |unsave| is not used when |cur_group=bottom_level|
        confusion("curlevel");
    }
}
// ~~~ End section 281 ~~~

// ~~~ Section 288 ~~~
void prepare_mag() {
    if (mag_set > 0 && mag != mag_set) {
        print_err("Incompatible magnification (");
        print_int(mag);
        print(");");
        print_nl(" the previous value will be retained");
        help2("I can handle only one magnification ratio per job. So I've")
            ("reverted to the magnification you used earlier on this run.");
        int_error(mag_set);
        geq_word_define(INT_BASE + MAG_CODE, mag_set); // |mag = mag_set|
    }
    if (mag <= 0 || mag > 32768) {
        print_err("Illegal magnification has been changed to 1000");
        help1("The magnification ratio must be between 1 and 32768.");
        int_error(mag);
        geq_word_define(INT_BASE + MAG_CODE, 1000);
    }
    mag_set = mag;
}
// ~~~ End section 288 ~~~

// ~~~ Section 306 ~~~
void runaway() {
    pointer p = null; // head of runaway list
    if (scanner_status > SKIPPING) {
        print_nl("Runaway ");
        switch (scanner_status) {
        case DEFINING:
            print("definition");
            p = def_ref;
            break;
        
        case MATCHING:
            print("argument");
            p = TEMP_HEAD;
            break;
        
        case ALIGNING:
            print("preamble");
            p = HOLD_HEAD;
            break;
        
        case ABSORBING:
            print("text");
            p = def_ref;
        } // there are no other cases
        print_char('?');
        print_ln();
        show_token_list(link(p), null, ERROR_LINE - 10);
    }
}
// ~~~ End section 306 ~~~

// ~~~ Section 323 ~~~
void begin_token_list(pointer p, quarterword t) {
    push_input;
    state = TOKEN_LIST;
    start = p;
    token_type = t;
    if (t >= MACRO) {
        // the token list starts with a reference count
        add_token_ref(p);
        if (t == MACRO) {
            param_start = param_ptr;
        }
        else {
            loc = link(p);
            if (tracing_macros > 1) {
                begin_diagnostic();
                print_nl("");
                switch (t) {
                case MARK_TEXT:
                    print_esc("mark");
                    break;
                
                case WRITE_TEXT:
                    print_esc("write");
                    break;
                
                default:
                    print_cmd_chr(ASSIGN_TOKS, t - OUTPUT_TEXT + OUTPUT_ROUTINE_LOC);
                }
                print("->");
                token_show(p);
                end_diagnostic(false);
            }
        }
    }
    else {
        loc = p;
    }
}
// ~~~ End section 323 ~~~

// ~~~ Section 324 ~~~
// leave a token-list input level
void end_token_list() {
    if (token_type >= BACKED_UP) {
        // token list to be deleted
        if (token_type <= INSERTED) {
            flush_list(start);
        }
        else {
            // update reference count
            delete_token_ref(start);
            if (token_type == MACRO) {
                // parameters must be flushed
                while (param_ptr > param_start) {
                    decr(param_ptr);
                    flush_list(param_stack[param_ptr]);
                }
            }
        }
    }
    else if (token_type == U_TEMPLATE) {
        if (align_state > 500000) {
            align_state = 0;
        }
        else {
            fatal_error("(interwoven alignment preambles are not allowed)");
        }
    }
    pop_input;
    check_interrupt;
}
// ~~~ End section 324 ~~~

// ~~~ Section 325 ~~~
// undoes one token of input
void back_input() {
    pointer p; // a token list of length one
    while (state == TOKEN_LIST
        && loc == null
        && token_type != V_TEMPLATE)
    {
        // conserve stack space
        end_token_list();
    }
    p = get_avail();
    info(p) = cur_tok;
    if (cur_tok < RIGHT_BRACE_LIMIT) {
        if (cur_tok < LEFT_BRACE_LIMIT) {
            decr(align_state);
        }
        else {
            incr(align_state);
        }
    }
    push_input;
    state = TOKEN_LIST;
    start = p;
    token_type = BACKED_UP;
    loc = p; // that was |back_list(p)|, without procedure overhead
}
// ~~~ End section 325 ~~~

// ~~~ Section 327 ~~~
// back up one token and call |error|
void back_error() {
    ok_to_interrupt = false;
    back_input();
    ok_to_interrupt = true;
    error();
}

// back up one inserted token and call |error|
void ins_error() {
    ok_to_interrupt = false;
    back_input();
    token_type = INSERTED;
    ok_to_interrupt = true;
    error();
}
// ~~~ End section 327 ~~~

// ~~~ Section 328 ~~~
void begin_file_reading() {
    if (in_open == MAX_IN_OPEN) {
        overflow("text input levels", MAX_IN_OPEN);
    }
    if (first == BUF_SIZE) {
        overflow("buffer size", BUF_SIZE);
    }
    incr(in_open);
    push_input;
    index = in_open;
    line_stack[index] = line;
    start = first;
    state = MID_LINE;
    name = 0; // |terminal_input| is now |true|
}
// ~~~ End section 328 ~~~

// ~~~ Section 329 ~~~
void end_file_reading() {
    first = start;
    line = line_stack[index];
    if (name > 17) {
        a_close(cur_file); // forget it
    }
    pop_input;
    decr(in_open);
}
// ~~~ End section 329 ~~~
