// ~~~ Section 403 ~~~
// ~~~ Start file |subroutines.c|, 1382 ~~~
#include <string.h>
#include "arithmetic.h"
#include "builder.h"
#include "texerror.h"
#include "font_metric.h"
#include "parser.h"
// ~~~ End section 1382 ~~~

// reads a mandatory |LEFT_BRACE|
void scan_left_brace() {
    // ~~~ Get the next non-blank non-relax non-call token, 404 ~~~
    do {
        get_x_token();
    } while (cur_cmd == SPACER || cur_cmd == RELAX);
    // ~~~ End section 404 ~~~
    if (cur_cmd != LEFT_BRACE) {
        print_err("Missing { inserted");
        help4("A left brace was mandatory here, so I've put one in.")
            ("You might want to delete and/or insert some corrections")
            ("so that I will find a matching right brace soon.")
            ("(If you're confused by all this, try typing `I}' now.)");
        back_error();
        cur_tok = LEFT_BRACE_TOKEN + '{';
        cur_cmd = LEFT_BRACE;
        cur_chr = '{';
        incr(align_state);
    }
}
// ~~~ End section 403 ~~~

// ~~~ Section 405 ~~~
void scan_optional_equals() {
    // ~~~ Get the next non-blank non-call token, 406 ~~~
    do {
        get_x_token();
    } while (cur_cmd == SPACER);
    // ~~~ End section 406 ~~~
    if (cur_tok != OTHER_TOKEN + '=') {
        back_input();
    }
}
// ~~~ End section 405 ~~~

// ~~~ Section 407 ~~~
// look for a given string
bool scan_keyword(char *s) {
    pointer p; // tail of the backup list
    pointer q; // new node being added to the token list via |store_new_token|
    int k; // index into the string |s|
    int len = strlen(s);
    p = BACKUP_HEAD;
    link(p) = null;
    k = 0;
    while (k < len) {
        get_x_token(); // recursion is possible here
        if (cur_cs == 0
            && (cur_chr == s[k] || cur_chr == s[k] - 'a' + 'A'))
        {
            store_new_token(cur_tok);
            incr(k);
        }
        else if (cur_cmd != SPACER || p != BACKUP_HEAD) {
            back_input();
            if (p != BACKUP_HEAD) {
                back_list(link(BACKUP_HEAD));
            }
            return false;
        }
    }
    flush_list(link(BACKUP_HEAD));
    return true;
}
// ~~~ End section 407 ~~~

// ~~~ Section 409 ~~~
// ~~~ Declare procedures that scan restricted classes of integers, 433 ~~~
void scan_eight_bit_int() {
    scan_int();
    if (cur_val < 0 || cur_val > 255) {
        print_err("Bad register code");        
        help2("A register number must be between 0 and 255.")
            ("I changed this one to zero.");
        int_error(cur_val);
        cur_val = 0;
    }
}

// ~~~ Section 434 ~~~
void scan_char_num() {
    scan_int();
    if (cur_val < 0 || cur_val > 255) {
        print_err("Bad character code");
        help2("A character number must be between 0 and 255.")
            ("I changed this one to zero.");
        int_error(cur_val);
        cur_val = 0;
    }
}
// ~~~ End section 434 ~~~

// ~~~ Section 435 ~~~
void scan_four_bit_int() {
    scan_int();
    if (cur_val < 0 || cur_val > 15) {
        print_err("Bad number");
        help2("Since I expected to read a number between 0 and 15,")
            ("I changed this one to zero.");
        int_error(cur_val);
        cur_val = 0;
    }
}
// ~~~ End section 435 ~~~

// ~~~ Section 436 ~~~
void scan_fifteen_bit_int() {
    scan_int();
    if (cur_val < 0 ||  cur_val > 0x7fff) {
        print_err("Bad mathchar");
        help2("A mathchar number must be between 0 and 32767.")
            ("I changed this one to zero.");
        int_error(cur_val);
        cur_val = 0;
    }
}
// ~~~ End section 436 ~~~

// ~~~ Section 437 ~~~
void scan_twenty_seven_bit_int() {
    scan_int();
    if (cur_val < 0 || cur_val > 0x7ffffff) {
        print_err("Bad delimiter code");
        help2("A numeric delimiter code must be between 0 and 2^{27} - 1.")
            ("I changed this one to zero.");
        int_error(cur_val);
        cur_val = 0;
    }
}
// ~~~ End section 437 ~~~
// ~~~ End section 433 ~~~

// ~~~ Declare procedures that scan font-related stuff, 577 ~~~
void scan_font_ident() {
    internal_font_number f;
    halfword m;
    // ~~~ Get the next non-blank non-call token, 406 ~~~
    do {
        get_x_token();
    } while (cur_cmd == SPACER);
    // ~~~ End section 406 ~~~
    if (cur_cmd == DEF_FONT) {
        f = cur_font;
    }
    else if (cur_cmd == SET_FONT) {
        f = cur_chr;
    }
    else if (cur_cmd == DEF_FAMILY) {
        m = cur_chr;
        scan_four_bit_int();
        f = equiv(m + cur_val);
    }
    else {
        print_err("Missing font identifier");
        help2("I was looking for a control sequence whose")
            ("current meaning has been defined by \\font.");
        back_error();
        f = NULL_FONT;
    }
    cur_val = f;
}

// ~~~ Section 578 ~~~
// sets |cur_val| to |font_info| location
void find_font_dimen(bool writing) {
    internal_font_number f;
    int n; // the parameter number
    scan_int();
    n = cur_val;
    scan_font_ident();
    f = cur_val;
    if (n <= 0) {
        cur_val = fmem_ptr;
    }
    else {
        if (writing && n <= SPACE_SHRINK_CODE && n >= SPACE_CODE && font_glue[f] != null) {
            delete_glue_ref(font_glue[f]);
            font_glue[f] = null;
        }
        if (n > font_params[f]) {
            if (f < font_ptr) {
                cur_val = fmem_ptr;
            }
            else {
                // ~~~ Increase the number of parameters in the last font, 580 ~~~
                do {
                    if (fmem_ptr == FONT_MEM_SIZE) {
                        overflow("font memory", FONT_MEM_SIZE);
                    }
                    font_info[fmem_ptr].sc = 0;
                    incr(fmem_ptr);
                    incr(font_params[f]);
                } while (n != font_params[f]);
                cur_val = fmem_ptr - 1; // this equals |param_base[f] + font_params[f]|
                // ~~~ End section 580 ~~~
            }
        }
        else {
            cur_val = n + param_base[f];
        }
    }
    // ~~~ Issue an error message if |cur_val = fmem_ptr|, 579 ~~~
    if (cur_val == fmem_ptr) {
        print_err("Font ");
        print_esc_strnumber(font_id_text(f));
        print(" has only ");
        print_int(font_params[f]);
        print(" fontdimen parameters");
        help2("To increase the number of font parameters, you must")
            ("use \\fontdimen immediately after the \\font is loaded.");
        error();
    }
    // ~~~ End section 579 ~~~
}
// ~~~ End section 578 ~~~
// ~~~ End section 577 ~~~
// ~~~ End section 409 ~~~

// ~~~ Section 413 ~~~
// fetch an internal parameter
void scan_something_internal(small_number level, bool negative) {
    halfword m; // |chr_code| part of the operand token
    int p;      // index into |nest|
    m = cur_chr;
    switch (cur_cmd) {
    case DEF_CODE:
        // ~~~ Fetch a character code from some table, 414 ~~~
        scan_char_num();
        if (m == MATH_CODE_BASE) {
            scanned_result(ho(math_code(cur_val)), INT_VAL);
        }
        else if (m < MATH_CODE_BASE) {
            scanned_result(equiv(m + cur_val), INT_VAL);
        }
        else {
            scanned_result(eqtb[m + cur_val].integer, INT_VAL);
        }
        // ~~~ End section 414 ~~~
        break;
    
    case TOKS_REGISTER:
    case ASSIGN_TOKS:
    case DEF_FAMILY:
    case SET_FONT:
    case DEF_FONT:
        // ~~~ Fetch a token list or font identifier, provided that |level = TOK_VAL|, 415 ~~~
        if (level != TOK_VAL) {
            print_err("Missing number, treated as zero");
            help3("A number should have been here; I inserted `0'.")
                ("(If you can't figure out why I needed to see a number,")
                ("look up `weird error' in the index to The TeXbook.)");
            back_error();
            scanned_result(0, DIMEN_VAL);
        }
        else if (cur_cmd <= ASSIGN_TOKS) {
            if (cur_cmd < ASSIGN_TOKS) {
                // |cur_cmd == TOKS_REGISTER|
                scan_eight_bit_int();
                m = TOKS_BASE + cur_val;
            }
            scanned_result(equiv(m), TOK_VAL);
        }
        else {
            back_input();
            scan_font_ident();
            scanned_result(FONT_ID_BASE + cur_val, IDENT_VAL);
        }
        // ~~~ End section 415 ~~~
        break;
    
    case ASSIGN_INT:
        scanned_result(eqtb[m].integer, INT_VAL);
        break;
    
    case ASSIGN_DIMEN:
        scanned_result(eqtb[m].sc, DIMEN_VAL);
        break;
    
    case ASSIGN_GLUE:
        scanned_result(equiv(m), GLUE_VAL);
        break;
    
    case ASSIGN_MU_GLUE:
        scanned_result(equiv(m), MU_VAL);
        break;
    
    case SET_AUX:
        // ~~~ Fetch the |space_factor| or the |prev_depth|, 418 ~~~
        if (abs(mode) != m) {
            print_err("Improper ");
            print_cmd_chr(SET_AUX, m);
            help4("You can refer to \\spacefactor only in horizontal mode;")
                ("you can refer to \\prevdepth only in vertical mode; and")
                ("neither of these is meaningful inside \\write. So")
                ("I'm forgetting what you said and using zero instead.");
            error();
            if (level != TOK_VAL) {
                scanned_result(0, DIMEN_VAL);
            }
            else {
                scanned_result(0, INT_VAL);
            }
        }
        else if (m == VMODE) {
            scanned_result(prev_depth, DIMEN_VAL);
        }
        else {
            scanned_result(space_factor, INT_VAL);
        }
        // ~~~ End section 418 ~~~
        break;
    
    case SET_PREV_GRAF:
        // ~~~ Fetch the |prev_graf|, 422 ~~~
        if (mode == 0) {
            scanned_result(0, INT_VAL); // |prev_graf == 0| within \write
        }
        else {
            nest[nest_ptr] = cur_list;
            p = nest_ptr;
            while (abs(nest[p].mode_field) != VMODE) {
                decr(p);
            }
            scanned_result(nest[p].pg_field, INT_VAL);
        }
        // ~~~ End section 422 ~~~
        break;
    
    case SET_PAGE_INT:
        // ~~~ Fetch the |dead_cycles| or the |insert_penalties|, 419 ~~~
        if (m == 0) {
            cur_val = dead_cycles;
        }
        else {
            cur_val = insert_penalties;
        }
        cur_val_level = INT_VAL;
        // ~~~ End section 419 ~~~
        break;
    
    case SET_PAGE_DIMEN:
        // ~~~ Fetch something on the |page_so_far|, 421 ~~~
        if (page_contents == EMPTY && !output_active) {
            if (m == 0) {
                cur_val = MAX_DIMEN;
            }
            else {
                cur_val = 0;
            }
        }
        else {
            cur_val = page_so_far[m];
        }
        cur_val_level = DIMEN_VAL;
        // ~~~ End section 421 ~~~
        break;
    
    case SET_SHAPE:
        // ~~~ Fetch the |par_shape| size, 423 ~~~
        if (par_shape_ptr == null) {
            cur_val = 0;
        }
        else {
            cur_val = info(par_shape_ptr);
        }
        cur_val_level = INT_VAL;
        // ~~~ End section 423 ~~~
        break;
    
    case SET_BOX_DIMEN:
        // ~~~ Fetch a box dimension, 420 ~~~
        scan_eight_bit_int();
        if (box(cur_val) == null) {
            cur_val = 0;
        }
        else {
            cur_val = mem[box(cur_val) + m].sc;
        }
        cur_val_level = DIMEN_VAL;
        // ~~~ End section 420 ~~~
        break;
    
    case CHAR_GIVEN:
    case MATH_GIVEN:
        scanned_result(cur_chr, INT_VAL);
        break;
    
    case ASSIGN_FONT_DIMEN:
        // ~~~ Fetch a font dimension, 425 ~~~
        find_font_dimen(false);
        font_info[fmem_ptr].sc = 0;
        scanned_result(font_info[cur_val].sc, DIMEN_VAL);
        // ~~~ End section 425 ~~~
        break;
    
    case ASSIGN_FONT_INT:
        // ~~~ Fetch a font integer, 426 ~~~
        scan_font_ident();
        if (m == 0) {
            scanned_result(hyphen_char[cur_val], INT_VAL);
        }
        else {
            scanned_result(skew_char[cur_val], INT_VAL);
        }
        // ~~~ End section 426 ~~~
        break;
    
    case REGISTER:
        // ~~~ Fetch a register, 427 ~~~
        scan_eight_bit_int();
        switch (m) {
        case INT_VAL:
            cur_val = count(cur_val);
            break;
        
        case DIMEN_VAL:
            cur_val = dimen(cur_val);
            break;
        
        case GLUE_VAL:
            cur_val = skip(cur_val);
            break;
        
        case MU_VAL:
            cur_val = mu_skip(cur_val);
        } // there are no other cases
        cur_val_level = m;
        // ~~~ End section 427 ~~~
        break;
    
    case LAST_ITEM:
        // ~~~ Fetch an item in the current node, if appropriate, 424 ~~~
        if (cur_chr > GLUE_VAL) {
            if (cur_chr == INPUT_LINE_NO_CODE) {
                cur_val = line;
            }
            else {
                cur_val = last_badness; // |cur_chr = BADNESS_CODE|
            }
            cur_val_level = INT_VAL;
        }
        else {
            if (cur_chr == GLUE_VAL) {
                cur_val = ZERO_GLUE;
            }
            else {
                cur_val = 0;
            }
            cur_val_level = cur_chr;
            if (!is_char_node(tail) && mode != 0) {
                switch (cur_chr) {
                case INT_VAL:
                    if (type(tail) == PENALTY_NODE) {
                        cur_val = penalty(tail);
                    }
                    break;
                
                case DIMEN_VAL:
                    if (type(tail) == KERN_NODE) {
                        cur_val = width(tail);
                    }
                    break;
                
                case GLUE_VAL:
                    if (type(tail) == GLUE_NODE) {
                        cur_val = glue_ptr(tail);
                        if (subtype(tail) == MU_GLUE) {
                            cur_val_level = MU_VAL;
                        }
                    }
                } // there are no other cases
            }
            else if (mode == VMODE && tail == head) {
                switch (cur_chr) {
                case INT_VAL:
                    cur_val = last_penalty;
                    break;
                
                case DIMEN_VAL:
                    cur_val = last_kern;
                    break;
        
                case GLUE_VAL:
                    if (last_glue != MAX_HALFWORD) {
                        cur_val = last_glue;
                    }
                } // there are no other cases
            }
        }
        // ~~~ End section 424 ~~~
        break;
    
    default:
        // ~~~ Complain that \the can't do this; give zero result, 428 ~~~
        print_err("You can't use `");
        print_cmd_chr(cur_cmd, cur_chr);
        print("' after ");
        print_esc("the");
        help1("I'm forgetting what you said and using zero instead.");
        error();
        if (level != TOK_VAL) {
            scanned_result(0, DIMEN_VAL);
        }
        else {
            scanned_result(0, INT_VAL);
        }
        // ~~~ End section 428 ~~~
    }
    while (cur_val_level > level) {
        // ~~~ Convert |cur_val| to a lower level, 429 ~~~
        if (cur_val_level == GLUE_VAL) {
            cur_val = width(cur_val);
        }
        else if (cur_val_level == MU_VAL) {
            mu_error();
        }
        decr(cur_val_level);
        // ~~~ End section 429 ~~~
    }
    // ~~~ Fix the reference count, if any, and negate |cur_val| if |negative|, 430 ~~~
    if (negative) {
        if (cur_val_level >= GLUE_VAL) {
            cur_val = new_spec(cur_val);
            // ~~~ Negate all three glue components of |cur_val|, 431 ~~~
            negate(width(cur_val));
            negate(stretch(cur_val));
            negate(shrink(cur_val));
            // ~~~ End section 431 ~~~
        }
        else {
            negate(cur_val);
        }
    }
    else if (cur_val_level >= GLUE_VAL && cur_val_level <= MU_VAL) {
        add_glue_ref(cur_val);
    }
    // ~~~ End section 430 ~~~
}
// ~~~ End section 413 ~~~

// ~~~ Section 440 ~~~
// sets |cur_val| to an integer
void scan_int() {
    bool negative;  // should the answer be negated?
    int m;          // |2^{31} / radix|, the threshold of danger
    small_number d; // the digit just scanned
    bool vacuous;   // have no digits appeared?
    bool ok_so_far; // has an error message been issued?

    radix = 0;
    ok_so_far = true;
    // ~~~ Get the next non-blank non-sign token; set |negative| appropriately, 441 ~~~
    negative = false;
    do {
        // ~~~ Get the next non-blank non-call token, 406 ~~~
        do {
            get_x_token();
        } while (cur_cmd == SPACER);
        // ~~~ End section 406 ~~~
        if (cur_tok == OTHER_TOKEN + '-') {
            negative = !negative;
            cur_tok = OTHER_TOKEN + '+';
        }
    } while (cur_tok == OTHER_TOKEN + '+');
    // ~~~ End section 441 ~~~
    if (cur_tok == ALPHA_TOKEN) {
        // ~~~ Scan an alphabetic character code into |cur_val|, 442 ~~~
        get_token(); // suppress macro expansion
        if (cur_tok < CS_TOKEN_FLAG) {
            cur_val = cur_chr;
            if (cur_cmd <= RIGHT_BRACE) {
                if (cur_cmd == RIGHT_BRACE) {
                    incr(align_state);
                }
                else {
                    decr(align_state);
                }
            }
        }
        else if (cur_tok < CS_TOKEN_FLAG + SINGLE_BASE) {
            cur_val = cur_tok - CS_TOKEN_FLAG - ACTIVE_BASE;
        }
        else {
            cur_val = cur_tok - CS_TOKEN_FLAG - SINGLE_BASE;
        }
        if (cur_val > 255) {
            print_err("Improper alphabetic constant");
            help2("A one-character control sequence belongs after a ` mark.")
                ("So I'm essentially inserting \\0 here.");
            cur_val = '0';
            back_error();
        }
        else {
            // ~~~ Scan an optional space, 443 ~~~
            get_x_token();
            if (cur_cmd != SPACER) {
                back_input();
            }
            // ~~~ End section 443 ~~~
        }
        // ~~~ End section 442 ~~~
    }
    else if (cur_cmd >= MIN_INTERNAL && cur_cmd <= MAX_INTERNAL) {
        scan_something_internal(INT_VAL, false);
    }
    else {
        // ~~~ Scan a numeric constant, 444 ~~~
        radix = 10;
        m = 214748364;
        if (cur_tok == OCTAL_TOKEN) {
            radix = 8;
            m = 0x10000000;
            get_x_token();
        }
        else if (cur_tok == HEX_TOKEN) {
            radix = 16;
            m = 0x8000000;
            get_x_token();
        }
        vacuous = true;
        cur_val = 0;
        // ~~~ Accumulate the constant until |cur_tok| is not a suitable digit, 445 ~~~
        while(true) {
            if (cur_tok < ZERO_TOKEN + radix
                && cur_tok >= ZERO_TOKEN
                && cur_tok <= ZERO_TOKEN + 9)
            {
                d = cur_tok - ZERO_TOKEN;
            }
            else if (radix == 16) {
                if (cur_tok <= A_TOKEN + 5 && cur_tok >= A_TOKEN) {
                    d = cur_tok - A_TOKEN + 10;
                }
                else if (cur_tok <= OTHER_A_TOKEN + 5 && cur_tok >= OTHER_A_TOKEN) {
                    d = cur_tok - OTHER_A_TOKEN + 10;
                }
                else {
                    break; // Goto done
                }
            }
            else {
                break; // Goto done
            }
            vacuous = false;
            if (cur_val >= m
                && (cur_val > m || d > 7 || radix != 10))
            {
                if (ok_so_far) {
                    print_err("Number too big");
                    help2("I can only go up to 2147483647='17777777777=\"7FFFFFFF,")
                        ("so I'm using that number instead of yours.");
                    error();
                    cur_val = INFINITY_;
                    ok_so_far = false;
                }
            }
            else {
                cur_val = cur_val * radix + d;
            }
            get_x_token();
        }
        // done:
        // ~~~ End section 445 ~~~
        if (vacuous) {
            // ~~~ Express astonishment that no number was here, 446 ~~~
            print_err("Missing number, treated as zero");
            help3("A number should have been here; I inserted `0'.")
                ("(If you can't figure out why I needed to see a number,")
                ("look up `weird error' in the index to The TeXbook.)");
            back_error();
            // ~~~ End section 446 ~~~
        }
        else if (cur_cmd != SPACER) {
            back_input();
        }
        // ~~~ End section 444 ~~~
    }
    if (negative) {
        negate(cur_val);
    }
}
// ~~~ End section 440 ~~~

// ~~~ Section 448 ~~~
// sets |cur_val| to a dimension
void scan_dimen(bool mu, bool inf, bool shortcut) {
    bool negative; // should the answer be negated?
    int f;         // numerator of a fraction whose denominator is $2^{16}$
    // ~~~ Local variables for dimension calculations, 450 ~~~
    int num, denom;   // conversion ratio for the scanned units
    int k, kk;        // number of digits in a decimal fraction
    pointer p, q;     // top of decimal digit stack
    scaled v;         // an internal dimension
    int save_cur_val; // temporary storage of |cur_val|
    // ~~~ End section 450 ~~~
    
    f = 0;
    arith_error = false;
    cur_order = NORMAL;
    negative = false;
    if (!shortcut) {
        // ~~~ Get the next non-blank non-sign token; set |negative| appropriately, 441 ~~~
        negative = false;
        do {
            // ~~~ Get the next non-blank non-call token, 406 ~~~
            do {
                get_x_token();
            } while (cur_cmd == SPACER);
            // ~~~ End section 406 ~~~
            if (cur_tok == OTHER_TOKEN + '-') {
                negative = !negative;
                cur_tok = OTHER_TOKEN + '+';
            }
        } while (cur_tok == OTHER_TOKEN + '+');
        // ~~~ End section 441 ~~~
        if (cur_cmd >= MIN_INTERNAL && cur_cmd <= MAX_INTERNAL) {
            // ~~~ Fetch an internal dimension and |goto attach_sign|, or fetch an internal integer, 449 ~~~
            if (mu) {
                scan_something_internal(MU_VAL, false);
                // ~~~ Coerce glue to a dimension, 451 ~~~
                if (cur_val_level >= GLUE_VAL) {
                    v = width(cur_val);
                    delete_glue_ref(cur_val);
                    cur_val = v;
                }
                // ~~~ End section 451 ~~~
                if (cur_val_level == MU_VAL) {
                    goto attach_sign;
                }
                if (cur_val_level != INT_VAL) {
                    mu_error();
                }
            }
            else {
                scan_something_internal(DIMEN_VAL, false);
                if (cur_val_level == DIMEN_VAL) {
                    goto attach_sign;
                }
            }
            // ~~~ End section 449 ~~~
        }
        else { 
            back_input();
            if (cur_tok == CONTINENTAL_POINT_TOKEN) {
                cur_tok = POINT_TOKEN;
            }
            if (cur_tok != POINT_TOKEN) {
                scan_int();
            }
            else {
                radix = 10;
                cur_val = 0;
            }
            if (cur_tok == CONTINENTAL_POINT_TOKEN) {
                cur_tok = POINT_TOKEN;
            }
            if (radix == 10 && cur_tok == POINT_TOKEN) {
                // ~~~ Scan decimal fraction, 452 ~~~
                k = 0;
                p = null;
                get_token(); // |POINT_TOKEN| is being re-scanned
                while(true) {
                    get_x_token();
                    if (cur_tok > ZERO_TOKEN + 9 || cur_tok < ZERO_TOKEN) {
                        break; // Goto done1
                    }
                    if (k < 17) {
                        // digits for |k >= 17| cannot affect the result
                        q = get_avail();
                        link(q) = p;
                        info(q) = cur_tok - ZERO_TOKEN;
                        p = q;
                        incr(k);
                    }
                }
                // done1:
                for(kk = k; kk >= 1; kk--) {
                    dig[kk - 1] = info(p);
                    q = p;
                    p = link(p);
                    free_avail(q);
                }
                f = round_decimals(k);
                if (cur_cmd != SPACER) {
                    back_input();
                }
                // ~~~ End section 452 ~~~
            }
        }
    }
    if (cur_val < 0) {
        // in this case |f = 0|
        negative = !negative;
        negate(cur_val);
    }
    
    // ~~~ Scan units and set |cur_val| to x * (|cur_val| + f/2^{16}), where there are |x| sp per unit; |goto attach_sign| if the units are internal, 453 ~~~
    if (inf) {
        // ~~~ Scan for |fil| units; |goto attach_fraction| if found, 454 ~~~
        if (scan_keyword("fil")) {
            cur_order = FIL;
            while (scan_keyword("l")) {
                if (cur_order == FILLL) {
                    print_err("Illegal unit of measure (");
                    print("replaced by filll)");
                    help1("I dddon't go any higher than filll.");
                    error();
                }
                else {
                    incr(cur_order);
                }
            }
            goto attach_fraction;
        }
        // ~~~ End section 454 ~~~
    }
    
    // ~~~ Scan for units that are internal dimensions; |goto attach_sign| with |cur_val| set if found, 455 ~~~
    save_cur_val = cur_val;
    // ~~~ Get the next non-blank non-call token, 406 ~~~
    do {
        get_x_token();
    } while (cur_cmd == SPACER);
    // ~~~ End section 406 ~~~
    if (cur_cmd < MIN_INTERNAL || cur_cmd > MAX_INTERNAL) {
        back_input();
    }
    else {
        if (mu) {
            scan_something_internal(MU_VAL, false);
            // ~~~ Coerce glue to a dimension, 451 ~~~
            if (cur_val_level >= GLUE_VAL) {
                v = width(cur_val);
                delete_glue_ref(cur_val);
                cur_val = v;
            }
            // ~~~ End section 451 ~~~
            if (cur_val_level != MU_VAL) {
                mu_error();
            }
        }
        else {
            scan_something_internal(DIMEN_VAL, false);
        }
        v = cur_val;
        goto found;
    }
    if (mu) {
        goto not_found;
    }
    if (scan_keyword("em")) {
        // ~~~ The em width for |cur_font|, 558 ~~~
        v = quad(cur_font);
        // ~~~ End section 558 ~~~
    }
    else if (scan_keyword("ex")) {
        // ~~~ The x-height for |cur_font|, 559 ~~~
        v = x_height(cur_font);
        // ~~~ End section 559 ~~~
    }
    else {
        goto not_found;
    }
    // ~~~ Scan an optional space, 443 ~~~
    get_x_token();
    if (cur_cmd != SPACER) {
        back_input();
    }
    // ~~~ End section 443 ~~~
    
found:
    cur_val = nx_plus_y(save_cur_val, v, xn_over_d(v, f, 0x10000));
    goto attach_sign;
not_found:
    // ~~~ End section 455 ~~~
    
    if (mu) {
        // ~~~ Scan for mu units and |goto attach_fraction|, 456 ~~~
        if (scan_keyword("mu")) {
            goto attach_fraction;
        }
        else {
            print_err("Illegal unit of measure (");
            print("mu inserted)");
            help4("The unit of measurement in math glue must be mu.")
                ("To recover gracefully from this error, it's best to")
                ("delete the erroneous units; e.g., type `2' to delete")
                ("two letters. (See Chapter 27 of The TeXbook.)");
            error();
            goto attach_fraction;
        }
        // ~~~ End section 456 ~~~
    }
    if (scan_keyword("true")) {
        // ~~~ Adjust for the magnification ratio, 457 ~~~
        prepare_mag();
        if (mag != 1000) {
            cur_val = xn_over_d(cur_val, 1000, mag);
            f = (1000*f + 0x10000 * remainder_) / mag;
            cur_val += f / 0x10000;
            f %= 0x10000;
        }
        // ~~~ End section 457 ~~~
    }
    if (scan_keyword("pt")) {
        goto attach_fraction; // the easy case
    }
    
    // ~~~ Scan for all other units and adjust |cur_val| and |f| accordingly; |goto done| in the case of scaled points, 458 ~~~
    if (scan_keyword("in")) {
        set_conversion(7227, 100);
    }
    else if (scan_keyword("pc")) {
        set_conversion(12, 1);
    }
    else if (scan_keyword("cm")) {
        set_conversion(7227, 254);
    }
    else if (scan_keyword("mm")) {
        set_conversion(7227, 2540);
    }
    else if (scan_keyword("bp")) {
        set_conversion(7227, 7200);
    }
    else if (scan_keyword("dd")) {
        set_conversion(1238, 1157);
    }
    else if (scan_keyword("cc")) {
        set_conversion(14856, 1157);
    }
    else if (scan_keyword("sp")) {
        goto done;
    }
    else {
        // ~~~ Complain about unknown unit and |goto done2|, 459 ~~~
        print_err("Illegal unit of measure (");
        print("pt inserted)");
        help6("Dimensions can be in units of em, ex, in, pt, pc,")
            ("cm, mm, dd, cc, bp, or sp; but yours is a new one!")
            ("I'll assume that you meant to say pt, for printer's points.")
            ("To recover gracefully from this error, it's best to")
            ("delete the erroneous units; e.g., type `2' to delete")
            ("two letters. (See Chapter 27 of The TeXbook.)");
        error();
        goto done2;
        // ~~~ End section 459 ~~~
    }
    cur_val = xn_over_d(cur_val, num, denom);
    f = (num * f + 0x10000 * remainder_) / denom;
    cur_val += f / 0x10000;
    f %= 0x10000;
done2:
    // ~~~ End section 458 ~~~
    
attach_fraction:
    if (cur_val >= 0x4000) {
        arith_error = true;
    }
    else {
        cur_val = cur_val * UNITY + f;
    }
done:
    // ~~~ End section 453 ~~~
    
    // ~~~ Scan an optional space, 443 ~~~
    get_x_token();
    if (cur_cmd != SPACER) {
        back_input();
    }
    // ~~~ End section 443 ~~~

attach_sign:
    if (arith_error || abs(cur_val) >= 0x40000000) {
        // ~~~ Report that this dimension is out of range, 460 ~~~
        print_err("Dimension too large");
        help2("I can't work with sizes bigger than about 19 feet.")
            ("Continue and I'll use the largest value I can.");
        error();
        cur_val = MAX_DIMEN;
        arith_error = false;
        // ~~~ End section 460 ~~~
    }
    if (negative) {
        negate(cur_val);
    }
}
// ~~~ End section 448 ~~~

// ~~~ Section 461 ~~~
// sets |cur_val| to a glue spec pointer
void scan_glue(small_number level) {
    bool negative; // should the answer be negated?
    pointer q;     // new glue specification
    bool mu;       // does |level = MU_VAL|?

    mu = (level == MU_VAL);
    // ~~~ Get the next non-blank non-sign token; set |negative| appropriately, 441 ~~~
    negative = false;
    do {
        // ~~~ Get the next non-blank non-call token, 406 ~~~
        do {
            get_x_token();
        } while (cur_cmd == SPACER);
        // ~~~ End section 406 ~~~
        if (cur_tok == OTHER_TOKEN + '-') {
            negative = !negative;
            cur_tok = OTHER_TOKEN + '+';
        }
    } while (cur_tok == OTHER_TOKEN + '+');
    // ~~~ End section 441 ~~~
    if (cur_cmd >= MIN_INTERNAL && cur_cmd <= MAX_INTERNAL) {
        scan_something_internal(level, negative);
        if (cur_val_level >= GLUE_VAL) {
            if (cur_val_level != level) {
                mu_error();
            }
            return;
        }
        if (cur_val_level == INT_VAL) {
            scan_dimen(mu, false, true);
        }
        else if (level == MU_VAL) {
            mu_error();
        }
    }
    else {
        back_input();
        scan_dimen(mu, false, false);
        if (negative) {
            negate(cur_val);
        }
    }
    // ~~~ Create a new glue specification whose width is |cur_val|; scan for its stretch and shrink components, 462 ~~~
    q = new_spec(ZERO_GLUE);
    width(q) = cur_val;
    if (scan_keyword("plus")) {
        scan_dimen(mu, true, false);
        stretch(q) = cur_val;
        stretch_order(q) = cur_order;
    }
    if (scan_keyword("minus")) {
        scan_dimen(mu, true, false);
        shrink(q) = cur_val;
        shrink_order(q) = cur_order;
    }
    cur_val = q;
    // ~~~ End section 462 ~~~
}
// ~~~ End section 461 ~~~

// ~~~ Section 463 ~~~
pointer scan_rule_spec() {
    pointer q; // the rule node being created
    q = new_rule(); // |width|, |depth|, and |height| all equal |NULL_FLAG| now
    if (cur_cmd == VRULE) {
        width(q) = DEFAULT_RULE;
    }
    else {
        height(q) = DEFAULT_RULE;
        depth(q) = 0;
    }
reswitch:
    if (scan_keyword("width")) {
        scan_normal_dimen;
        width(q) = cur_val;
        goto reswitch;
    }
    if (scan_keyword("height")) {
        scan_normal_dimen;
        height(q) = cur_val;
        goto reswitch;
    }
    if (scan_keyword("depth")) {
        scan_normal_dimen;
        depth(q) = cur_val;
        goto reswitch;
    }
    return q;
}
// ~~~ End section 463 ~~~

// ~~~ Section 645 ~~~
// scans a box specification and left brace
void scan_spec(int c, bool three_codes) {
    int s; // temporarily saved value
    int spec_code;
    if (three_codes) {
        s = saved(0);
    }
    if (scan_keyword("to")) {
        spec_code = EXACTLY;
    }
    else if (scan_keyword("spread")) {
        spec_code = ADDITIONAL;
    }
    else {
        spec_code = ADDITIONAL;
        cur_val = 0;
        goto found;
    }
    scan_normal_dimen;
found:
    if (three_codes) {
        saved(0) = s;
        incr(save_ptr);
    }
    saved(0) = spec_code;
    saved(1) = cur_val;
    save_ptr += 2;
    new_save_level(c);
    scan_left_brace();
}
// ~~~ End section 645 ~~~
