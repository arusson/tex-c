// ~~~ Section 311 ~~~
// ~~~ Start file |display_context.c|, 1382 ~~~
#include "datastructures.h"
#include "io.h"
// ~~~ End section 1382 ~~~

// prints where the scanner is
void show_context() {
    int old_setting;  // saved |selector| setting
    int nn;           // number of contexts shown so far, less one
    bool bottom_line; // have we reached the final context to be shown?
    // ~~~ Local variables for formatting calculations, 315 ~~~
    int i;  // index into |buffer|
    int j;  // end of current line in |buffer|
    int l;  // length of descriptive information on line 1
    int m;  // context information gathered for line 2
    int n;  // length of line 1
    int p;  // starting or ending place in |trick_buf|
    int q;  // temporary index
    // ~~~ End section 315 ~~~
    
    base_ptr = input_ptr;
    input_stack[base_ptr] = cur_input; // store current state
    nn = -1;
    bottom_line = false;
    while(true) {
        cur_input = input_stack[base_ptr]; // enter into the context
        if (state != TOKEN_LIST
            && (name > 17 || base_ptr == 0))
        {
            bottom_line = true;
        }
        if (base_ptr == input_ptr
            || bottom_line
            || nn < error_context_lines)
        {
            // ~~~ Display the current context, 312 ~~~
            if (base_ptr == input_ptr
                || state != TOKEN_LIST
                || token_type != BACKED_UP
                || loc != null)
            {
                // we omit backed-up token lists that have already been read
                tally = 0; // get ready to count characters
                old_setting = selector;
                if (state != TOKEN_LIST) {
                    // ~~~ Print location of current line, 313 ~~~
                    if (name <= 17) {
                        if (terminal_input) {
                            if (base_ptr == 0) {
                                print_nl("<*>");
                            }
                            else {
                                print_nl("<insert> ");
                            }
                        }
                        else {
                            print_nl("<read ");
                            if (name == 17) {
                                print_char('*');
                            }
                            else {
                                print_int(name - 1);
                            }
                            print_char('>');
                        }
                    }
                    else {
                        print_nl("l.");
                        print_int(line);
                    }
                    print_char(' ');
                    // ~~~ End section 313 ~~~
                    // ~~~ Pseudoprint the line, 318 ~~~
                    begin_pseudoprint;
                    if (buffer[limit] == end_line_char) {
                        j = limit;
                    }
                    else {
                        j = limit + 1; // determine the effective end of the line
                    }
                    if (j > 0) {
                        for(i = start; i < j; i++) {
                            if (i == loc) {
                                set_trick_count;
                            }
                            print_strnumber(buffer[i]);
                        }
                    }
                    // ~~~ End section 318 ~~~
                }
                else {
                    // ~~~ Print type of token list, 314 ~~~
                    switch (token_type) {
                    case PARAMETER:
                        print_nl("<argument> ");
                        break;
                    
                    case U_TEMPLATE:
                    case V_TEMPLATE:
                        print_nl("<template> ");
                        break;
                    
                    case BACKED_UP:
                        if (loc == null) {
                            print_nl("<recently read> ");
                        }
                        else {
                            print_nl("<to be read again> ");
                        }
                        break;
                    
                    case INSERTED:
                        print_nl("<inserted text> ");
                        break;
                    
                    case MACRO:
                        print_ln();
                        print_cs(name);
                        break;
                    
                    case OUTPUT_TEXT:
                        print_nl("<output> ");
                        break;
                    
                    case EVERY_PAR_TEXT:
                        print_nl("<everypar> ");
                        break;
                    
                    case EVERY_MATH_TEXT:
                        print_nl("<everymath> ");
                        break;
                    
                    case EVERY_DISPLAY_TEXT:
                        print_nl("<everydisplay> ");
                        break;
                    
                    case EVERY_HBOX_TEXT:
                        print_nl("<everyhbox> ");
                        break;
                    
                    case EVERY_VBOX_TEXT:
                        print_nl("<everyvbox> ");
                        break;
                    
                    case EVERY_JOB_TEXT:
                        print_nl("<everyjob> ");
                        break;
                    
                    case EVERY_CR_TEXT:
                        print_nl("<everycr> ");
                        break;
                    
                    case MARK_TEXT:
                        print_nl("<mark> ");
                        break;
                    
                    case WRITE_TEXT:
                        print_nl("<write> ");
                        break;
                    
                    default:
                        print_nl("?"); // this should never happen
                    }
                    // ~~~ End section 314 ~~~
                    // ~~~ Pseudoprint the token list, 319 ~~~
                    begin_pseudoprint;
                    if (token_type < MACRO) {
                        show_token_list(start, loc, 100000);
                    }
                    else {
                        show_token_list(link(start), loc, 100000); // avoid reference count
                    }
                    // ~~~ End section 319 ~~~
                }
                selector = old_setting; // stop pseudoprinting
                // ~~~ Print two lines using the tricky pseudoprinted information, 317 ~~~
                if (trick_count == 1000000) {
                    // |set_trick_count| must be performed
                    set_trick_count;
                }
                if (tally < trick_count) {
                    m = tally - first_count;
                }
                else {
                    // context on line 2
                    m = trick_count - first_count;
                }
                if (l + first_count <= HALF_ERROR_LINE) {
                    p = 0;
                    n = l + first_count;
                }
                else {
                    print("...");
                    p = l + first_count - HALF_ERROR_LINE + 3;
                    n = HALF_ERROR_LINE;
                }
                for(q = p; q < first_count; q++) {
                    print_char(trick_buf[q % ERROR_LINE]);
                }
                print_ln();
                for(q = 1; q <= n; q++) {
                    print_char(' '); // print |n| spaces to begin line 2
                }
                if (m + n <= ERROR_LINE) {
                    p = first_count + m;
                }
                else {
                    p = first_count + (ERROR_LINE - n - 3);
                }
                for(q = first_count; q < p; q++) {
                    print_char(trick_buf[q % ERROR_LINE]);
                }
                if (m + n > ERROR_LINE) {
                    print("...");
                }
                // ~~~ End section 317 ~~~
                incr(nn);
            }
            // ~~~ End section 312 ~~~
        }
        else if (nn == error_context_lines) {
            print_nl("...");
            incr(nn); // omitted if |error_context_lines < 0|
        }
        if (bottom_line) {
            break; // Goto done
        }
        decr(base_ptr);
    }
    // done:
    cur_input = input_stack[input_ptr]; // restore original state
}
// ~~~ End section 311 ~~~
