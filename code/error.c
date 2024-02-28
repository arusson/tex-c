// ~~~ Section 81 ~~~
// ~~~ Start file |error.c|, 1382 ~~~
#include <stdlib.h>
#include "texerror.h"
#include "datastructures.h"
#include "parser.h"
// ~~~ End section 1382 ~~~

void jump_out() {
    close_files_and_terminate();
    exit(0);
}
// ~~~ End section 81 ~~~

// ~~~ Section 82 ~~~
void error() {
    ASCII_code c;       // what the user types
    int s1, s2, s3, s4; // used to save global variables when deleting tokens
    if (history < ERROR_MESSAGE_ISSUED) {
        history = ERROR_MESSAGE_ISSUED;
    }
    print_char('.');
    show_context();
    if (interaction == ERROR_STOP_MODE) {
        // ~~~ Get user's advice and |return|, 83 ~~~
        while(true) {
            if (interaction != ERROR_STOP_MODE) {
                return;
            }
            clear_for_error_prompt();
            prompt_input("? ");
            if (last == first) {
                return;
            }
            c = buffer[first];
            if (c >= 'a') {
                c += 'A' - 'a'; // onvert to uppercase.
            }
            // ~~~ Interpret code |c| and |return| if done, 84 ~~~
            switch(c) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '7':
            case '8':
            case '9':
                if (deletions_allowed) {
                    // ~~~ Delete |c - '0'| tokens and |goto continue|, 88 ~~~
                    s1 = cur_tok;
                    s2 = cur_cmd;
                    s3 = cur_chr;
                    s4 = align_state;
                    align_state = 1000000;
                    ok_to_interrupt = false;
                    if (last > first + 1
                        && buffer[first + 1] >= '0'
                        && buffer[first + 1] <= '9')
                    {
                        c = c * 10 + buffer[first + 1] - '0' * 11;
                    }
                    else {
                        c -= '0';
                    }
                    while (c > 0) {
                        get_token(); // one-level recursive call of |error| is possible
                        decr(c);
                    }
                    cur_tok = s1;
                    cur_cmd = s2;
                    cur_chr = s3;
                    align_state = s4;
                    ok_to_interrupt = true;
                    help2("I have just deleted some text, as you asked.")
                        ("You can now delete more, or insert, or whatever.");
                    show_context();
                    continue;
                    // ~~~ End section 88 ~~~
                }
                break;
            
#ifdef DEBUG
            case 'D':
                debug_help();
                continue;
#endif
            
            case 'H':
                // ~~~ Print the help information and |goto continue|, 89 ~~~
                if (use_err_help) {
                    give_err_help();
                    use_err_help = false;
                }
                else {
                    if (help_ptr == 0) {
                        help2("Sorry, I don't know how to help in this situation.")
                            ("Maybe you should try asking a human?");
                    }
                    do {
                        decr(help_ptr);
                        print(help_line[help_ptr]);
                        print_ln();
                    } while (help_ptr != 0);
                }
                help4("Sorry, I already gave what help I could...")
                    ("Maybe you should try asking a human?")
                    ("An error might have occurred before I noticed any problems.")
                    ("``If all else fails, read the instructions.''");
                continue;
                // ~~~ End section 89 ~~~
                break;
            
            case 'I':
                // ~~~ Introduce new material from the terminal and |return|, 87 ~~~
                begin_file_reading(); // enter a new syntactic level for terminal input
                // now |state = MID_LINE|, so an initial blank space will count as a blank
                if (last > first + 1) {
                    loc = first + 1;
                    buffer[first] = ' ';
                }
                else {
                    prompt_input("insert>");
                    loc = first;
                }
                first = last;
                cur_input.limit_field = last - 1;  // no |end_line_char| ends this line
                return;
                // ~~~ End section 87 ~~~
                break;
            
            case 'Q':
            case 'R':
            case 'S':
                // ~~~ Change the interaction level and |return|, 86 ~~~
                error_count = 0;
                interaction = BATCH_MODE + c - 'Q';
                print("OK, entering ");
                switch(c) {
                case 'Q':
                    print_esc("batchmode");
                    decr(selector);
                    break;
                
                case 'R':
                    print_esc("nonstopmode");
                    break;
                
                case 'S':
                    print_esc("scrollmode");
                    break;
                } // there are no other cases
                print("...");
                print_ln();
                update_terminal;
                return;
                // ~~~ End section 86 ~~~
                break;
            
            case 'X':
                interaction = SCROLL_MODE;
                jump_out();
            
            default:
                do_nothing;
            }
            // ~~~ Print the menu of available options, 85 ~~~
            print("Type <return> to proceed, S to scroll future error messages,");
            print_nl("R to run without stopping, Q to run quietly,");
            print_nl("I to insert something, ");
            if (deletions_allowed) {
                print_nl("1 or .... or 9 to ignore the next 1 to 9 tokens of input,");
            }
            print_nl("H for help, X to quit.");
            // ~~~ End section 85 ~~~
            // ~~~ End section 84 ~~~
        }
        // ~~~ End section 83 ~~~
    }
    incr(error_count);
    if (error_count == 100) {
        print_nl("(That makes 100 errors; please try again.)");
        history = FATAL_ERROR_STOP;
        jump_out();
    }
    // ~~~ Put help message on the transcript file, 90 ~~~
    if (interaction > BATCH_MODE) {
        decr(selector); // avoid terminal output
    }
    if (use_err_help) {
        print_ln();
        give_err_help();
    }
    else {
        while (help_ptr > 0) {
            decr(help_ptr);
            print_nl(help_line[help_ptr]);
        }
    }
    print_ln();
    if (interaction > BATCH_MODE) {
        incr(selector); // re-enable terminal output
    }
    print_ln();
    // ~~~ End section 90 ~~~
}
// ~~~ End section 82 ~~~

// ~~~ Section 91 ~~~
void int_error(int n) {
    print(" (");
    print_int(n);
    print_char(')');
    error();
}
// ~~~ End section 91 ~~~

// ~~~ Section 92 ~~~
void normalize_selector() {
    if (log_opened) {
        selector = TERM_AND_LOG;
    }
    else {
        selector = TERM_ONLY;
    }

    if (job_name == 0) {
        open_log_file();
    }
    if (interaction == BATCH_MODE) {
        decr(selector);
    }
}
// ~~~ End section 92 ~~~

// ~~~ Section 93 ~~~
void succumb() {
    if (interaction == ERROR_STOP_MODE) {
        interaction = SCROLL_MODE; // no more interaction
    }
    if (log_opened) {
        error();
    }
#ifdef DEBUG
    if (interaction > BATCH_MODE) {
        debug_help();
    }
#endif
    history = FATAL_ERROR_STOP;
    jump_out(); // irrecoverable error
}

// prints |s| and that's it
void fatal_error(char *s) {
    normalize_selector();
    print_err("Emergency stop");
    help1(s);
    succumb();
}
// ~~~ End section 93 ~~~

// ~~~ Section 94 ~~~
// stop due to finiteness
void overflow(char *s, int n) {
    normalize_selector();
    print_err("TeX capacity exceeded, sorry [");
    print(s);
    print_char('=');
    print_int(n);
    print_char(']');
    help2("If you really absolutely need more capacity,")
        ("you can ask a wizard to enlarge me.");
    succumb();
}
// ~~~ End section 94 ~~~

// ~~~ Section 95 ~~~
// consistency check violated; |s| tells where
void confusion(char *s) {
    normalize_selector();
    if (history < ERROR_MESSAGE_ISSUED) {
        print_err("This can't happen (");
        print(s);
        print_char(')');
        help1("I´m broken. Please show this to someone who can fix can fix");
    }
    else {
        print_err("I can't go on meeting you like this");
        help2("One of your faux pas seems to have wounded me deeply...")
            ("in fact, I'm barely conscious. Please fix it and try again.");
    }
    succumb();
}
// ~~~ End section 95 ~~~

// ~~~ Section 98 ~~~
void pause_for_instructions() {
    if (ok_to_interrupt) {
        interaction = ERROR_STOP_MODE;
        if (selector == LOG_ONLY || selector == NO_PRINT) {
            incr(selector);
        }
        print_err("Interruption");
        help3("You rang?")
            ("Try to insert an instruction for me (e.g. `I\\showlists'),")
            ("unless you just want to quit by typing `X'.");
        deletions_allowed = false;
        error();
        deletions_allowed = true;
        interrupt = 0;
    }
}
// ~~~ End section 98 ~~~

// ~~~ Section 330 ~~~
void clear_for_error_prompt() {
    while (state != TOKEN_LIST
        && terminal_input
        && input_ptr > 0
        && loc > limit)
    {
        end_file_reading();
    }
    print_ln();
    clear_terminal;
}
// ~~~ End section 330 ~~~

// ~~~ Section 408 ~~~
void mu_error() {
    print_err("Incompatible glue units");
    help1("I'm going to assume that 1mu=1pt when they're mixed.");
    error();
}
// ~~~ End section 408 ~~~

// ~~~ Section 1127 ~~~
void align_error() {
    if (abs(align_state) > 2) {
        // ~~~ Express consternation over the fact that no alignment is in progress, 1128 ~~~
        print_err("Misplaced ");
        print_cmd_chr(cur_cmd, cur_chr);
        if (cur_tok == TAB_TOKEN + '&') {
            help6("I can't figure out why you would want to use a tab mark")
                ("here. If you just want an ampersand, the remedy is")
                ("simple: Just type `I\\&' now. But if some right brace")
                ("up above has ended a previous alignment prematurely,")
                ("you're probably due for more error messages, and you")
                ("might try typing `S' now just to see what is salvageable.");
        }
        else {
            help5("I can't figure out why you would want to use a tab mark")
                ("or \\cr or \\span just now. If something like a right brace")
                ("up above has ended a previous alignment prematurely,")
                ("you're probably due for more error messages, and you")
                ("might try typing `S' now just to see what is salvageable.");
        }
        error();
        // ~~~ End section 1128 ~~~
    }
    else {
        back_input();
        if (align_state < 0) {
            print_err("Missing { inserted");
            incr(align_state);
            cur_tok = LEFT_BRACE_TOKEN + '{';
        }
        else {
            print_err("Missing } inserted");
            decr(align_state);
            cur_tok = RIGHT_BRACE_TOKEN + '}';
        }
        help3("I've put in what seems to be necessary to fix")
            ("the current column of the current alignment.")
            ("Try to go on, since this might almost work.");
        ins_error();
    }
}
// ~~~ End section 1127 ~~~

// ~~~ Section 1284 ~~~
void give_err_help() {
    token_show(err_help);
}
// ~~~ End section 1284 ~~~
