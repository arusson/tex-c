// ~~~ Section 494 ~~~
// ~~~ Start file |conditional.c|, 1382 ~~~
#include "conditional.h"
#include "parser.h"
#include "texerror.h"
// ~~~ End section 1382 ~~~

void pass_text() {
    int l; // level of \if ... \fi nesting
    small_number save_scanner_status; // |scanner_status| upon entry
    save_scanner_status = scanner_status;
    scanner_status = SKIPPING;
    l = 0;
    skip_line = line;
    while(true) {
        get_next();
        if (cur_cmd == FI_OR_ELSE) {
            if (l == 0) {
                break; // Goto done
            }
            if (cur_chr == FI_CODE) {
                decr(l);
            }
        }
        else if (cur_cmd == IF_TEST) {
            incr(l);
        }
    }
    // done:
    scanner_status = save_scanner_status;
}
// ~~~ End section 494 ~~~

// ~~~ Section 497 ~~~
void change_if_limit(small_number l, pointer p) {
    pointer q;
    if (p == cond_ptr) {
        if_limit = l; // that's the easy case
    }
    else {
        q = cond_ptr;
        while(true) {
            if (q == null) {
                confusion("if");
            }
            if (link(q) == p) {
                type(q) = l;
                return;
            }
            q = link(q);
        }
    }
}
// ~~~ End section 497 ~~~

// ~~~ Section 498 ~~~
void conditional() {
    bool b = false;  // is the condition true?
    unsigned char r; // relation to be evaluated
    int m, n;        // to be tested against the second operand
    pointer p, q;    // for traversing token lists in \\ifx} tests
    small_number save_scanner_status; // |scanner_status| upon entry
    pointer save_cond_ptr;            // |cond_ptr| corresponding to this conditional
    small_number this_if;             // type of this conditional

    // ~~~ Push the condition stack, 495 ~~~
    p = get_node(IF_NODE_SIZE);
    link(p) = cond_ptr;
    type(p) = if_limit;
    subtype(p) = cur_if;
    if_line_field(p) = if_line;
    cond_ptr = p;
    cur_if = cur_chr;
    if_limit = IF_CODE;
    if_line = line;
    // ~~~ End section 495 ~~~
    save_cond_ptr = cond_ptr;
    this_if = cur_chr;
    // ~~~ Either process \ifcase or set |b| to the value of a boolean condition, 501 ~~~
    switch (this_if) {
    case IF_CHAR_CODE:
    case IF_CAT_CODE:
        // ~~~ Test if two characters match, 506 ~~~
        get_x_token_or_active_char;
        if (cur_cmd > ACTIVE_CHAR ||cur_chr > 255) {
            // not a character
            m = RELAX;
            n = 256;
        }
        else {
            m = cur_cmd;
            n = cur_chr;
        }
        get_x_token_or_active_char;
        if (cur_cmd > ACTIVE_CHAR || cur_chr > 255) {
            cur_cmd = RELAX;
            cur_chr = 256;
        }
        if (this_if == IF_CHAR_CODE) {
            b = (n == cur_chr);
        }
        else {
            b = (m == cur_cmd);
        }
        // ~~~ End section 506 ~~~
        break;
    
    case IF_INT_CODE:
    case IF_DIM_CODE:
        // ~~~ Test relation between integers or dimensions, 503 ~~~
        if (this_if == IF_INT_CODE) {
            scan_int();
        }
        else {
            scan_normal_dimen;
        }
        n = cur_val;
        // ~~~ Get the next non-blank non-call token, 406 ~~~
        do {
            get_x_token();
        } while (cur_cmd == SPACER);
        // ~~~ End section 406 ~~~
        if (cur_tok >= OTHER_TOKEN + '<' && cur_tok <= OTHER_TOKEN + '>') {
            r = cur_tok - OTHER_TOKEN;
        }
        else {
            print_err("Missing = inserted for ");
            print_cmd_chr(IF_TEST, this_if);
            help1("I was expecting to see `<', `=', or `>'. Didn't.");
            back_error();
            r = '=';
        }
        if (this_if == IF_INT_CODE) {
            scan_int();
        }
        else {
            scan_normal_dimen;
        }
        switch (r) {
        case '<':
            b = (n < cur_val);
            break;
        
        case '=':
            b = (n == cur_val);
            break;
        
        case '>':
            b = (n > cur_val);
        }
        // ~~~ End section 503 ~~~
        break;
    
    case IF_ODD_CODE:
        // ~~~ Test if an integer is odd, 504 ~~~
        scan_int();
        b = odd(cur_val);
        // ~~~ End section 504 ~~~
        break;
    
    case IF_VMODE_CODE:
        b = (abs(mode) == VMODE);
        break;
    
    case IF_HMODE_CODE:
        b = (abs(mode) == HMODE);
        break;
    
    case IF_MMODE_CODE:
        b = (abs(mode) == MMODE);
        break;
    
    case IF_INNER_CODE:
        b = (mode < 0);
        break;
    
    case IF_VOID_CODE:
    case IF_HBOX_CODE:
    case IF_VBOX_CODE:
        // ~~~ Test box register status, 505 ~~~
        scan_eight_bit_int();
        p = box(cur_val);
        if (this_if == IF_VOID_CODE) {
            b = (p == null);
        }
        else if (p == null) {
            b = false;
        }
        else if (this_if == IF_HBOX_CODE) {
            b = (type(p) == HLIST_NODE);
        }
        else {
            b = (type(p) == VLIST_NODE);
        }
        // ~~~ End section 505 ~~~
        break;
    
    case IFX_CODE:
        // ~~~ Test if two tokens match, 507 ~~~
        save_scanner_status = scanner_status;
        scanner_status = NORMAL;
        get_next();
        n = cur_cs;
        p = cur_cmd;
        q = cur_chr;
        get_next();
        if (cur_cmd != p) {
            b = false;
        }
        else if (cur_cmd < CALL) {
            b = (cur_chr == q);
        }
        else {
            // ~~~ Test if two macro texts match, 508 ~~~
            p = link(cur_chr);
            q = link(equiv(n)); // omit reference counts
            if (p == q) {
                b = true;
            }
            else {
                while (p != null && q != null) {
                    if (info(p) != info(q)) {
                        p = null;
                    }
                    else {
                        p = link(p);
                        q = link(q);
                    }
                }
                b = (p == null && q == null);
            }
            // ~~~ End section 508 ~~~
        }
        scanner_status = save_scanner_status;
        // ~~~ End section 507 ~~~
        break;
    
    case IF_EOF_CODE:
        scan_four_bit_int();
        b = (read_open[cur_val] == CLOSED);
        break;
    
    case IF_TRUE_CODE:
        b = true;
        break;
    
    case IF_FALSE_CODE:
        b = false;
        break;
    
    case IF_CASE_CODE:
        // ~~~ Select the appropriate case and |return| or |goto common_ending|, 509 ~~~
        scan_int();
        n = cur_val; // |n| is the number of cases to pass
        if (tracing_commands > 1) {
            begin_diagnostic();
            print("{case ");
            print_int(n);
            print_char('}');
            end_diagnostic(false);
        }
        while (n != 0) {
            pass_text();
            if (cond_ptr == save_cond_ptr) {
                if (cur_chr == OR_CODE) {
                    decr(n);
                }
                else {
                    goto common_ending;
                }
            }
            else if (cur_chr == FI_CODE) {
                // ~~~ Pop the condition stack, 496 ~~~
                p = cond_ptr;
                if_line = if_line_field(p);
                cur_if = subtype(p);
                if_limit = type(p);
                cond_ptr = link(p);
                free_node(p, IF_NODE_SIZE);
                // ~~~ End section 496 ~~~
            }
        }
        change_if_limit(OR_CODE, save_cond_ptr);
        return; // wait for \or, \else, or \fi
        // ~~~ End section 509 ~~~
    } // there are no other cases
    // ~~~ End section 501 ~~~
    if (tracing_commands > 1) {
        // ~~~ Display the value of |b|, 502 ~~~
        begin_diagnostic();
        if (b) {
            print("{true}");
        }
        else {
            print("{false}");
        }
        end_diagnostic(false);
        // ~~~ End section 502 ~~~
    }
    if (b) {
        change_if_limit(ELSE_CODE, save_cond_ptr);
        return; // wait for \else} or \fi
    }
    // ~~~ Skip to \else or \fi, then |goto common_ending|, 500 ~~~
    while(true){
        pass_text();
        if (cond_ptr == save_cond_ptr) {
            if (cur_chr != OR_CODE) {
                goto common_ending;
            }
            print_err("Extra ");
            print_esc("or");
            help1("I'm ignoring this; it doesn't match any \\if.");
            error();
        }
        else if (cur_chr == FI_CODE) {
            // ~~~ Pop the condition stack, 496 ~~~
            p = cond_ptr;
            if_line = if_line_field(p);
            cur_if = subtype(p);
            if_limit = type(p);
            cond_ptr = link(p);
            free_node(p, IF_NODE_SIZE);
            // ~~~ End section 496 ~~~
        }
    }
    // ~~~ End section 500 ~~~

common_ending:
    if (cur_chr == FI_CODE) {
        // ~~~ Pop the condition stack, 496 ~~~
        p = cond_ptr;
        if_line = if_line_field(p);
        cur_if = subtype(p);
        if_limit = type(p);
        cond_ptr = link(p);
        free_node(p, IF_NODE_SIZE);
        // ~~~ End section 496 ~~~
    }
    else {
        if_limit = FI_CODE; // wait for \fi
    }
}
// ~~~ End section 498 ~~~
