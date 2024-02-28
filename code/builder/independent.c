// ~~~ Section 1211 ~~~
// ~~~ Start file |independent.c|, 1382 ~~~
#include "builder.h"
#include "texerror.h"
#include "parser.h"
#include "arithmetic.h"
#include "font_metric.h"
// ~~~ End section 1382 ~~~

// ~~~ Declare subprocedures for |prefixed_command|, 1215 ~~~
void get_r_token() {
restart:
    do {
        get_token();
    } while (cur_tok == SPACE_TOKEN);
    if (cur_cs == 0 || cur_cs > FROZEN_CONTROL_SEQUENCE) {
        print_err("Missing control sequence inserted");
        help5("Please don't say `\\def cs{...}', say `\\def\\cs{...}'.")
            ("I've inserted an inaccessible control sequence so that your")
            ("definition will be completed without mixing me up too badly.")
            ("You can recover graciously from this error, if you're")
            ("careful; see exercise 27.2 in The TeXbook.");
        if (cur_cs == 0) {
            back_input();
        }
        cur_tok = CS_TOKEN_FLAG + FROZEN_PROTECTION;
        ins_error();
        goto restart;
    }
}

// ~~~ Section 1229 ~~~
void trap_zero_glue() {
    if (width(cur_val) == 0
        && stretch(cur_val) == 0
        && shrink(cur_val) == 0)
    {
        add_glue_ref(ZERO_GLUE);
        delete_glue_ref(cur_val);
        cur_val = ZERO_GLUE;
    }
}
// ~~~ End section 1229 ~~~

// ~~~ Section 1236 ~~~
void do_register_command(small_number a) {
    pointer l, q, r, s; // for list manipulation
    int p;              // type of register involved
    l = null;
    q = cur_cmd;
    // ~~~ Compute the register location |l| and its type |p|; but |return| if invalid, 1237 ~~~
    if (q != REGISTER) {
        get_x_token();
        if (cur_cmd >= ASSIGN_INT && cur_cmd <= ASSIGN_MU_GLUE) {
            l = cur_chr;
            p = cur_cmd - ASSIGN_INT;
            goto found;
        }
        if (cur_cmd != REGISTER) {
            print_err("You can't use `");
            print_cmd_chr(cur_cmd, cur_chr);
            print("' after ");
            print_cmd_chr(q, 0);
            help1("I'm forgetting what you said and not changing anything.");
            error();
            return;
        }
    }
    p = cur_chr;
    scan_eight_bit_int();
    switch (p) {
    case INT_VAL:
        l = cur_val + COUNT_BASE;
        break;
    
    case DIMEN_VAL:
        l = cur_val + SCALED_BASE;
        break;
    
    case GLUE_VAL:
        l = cur_val + SKIP_BASE;
        break;
    
    case MU_VAL:
        l = cur_val + MU_SKIP_BASE;
    } // there are no other cases
found:
    // ~~~ End section 1237 ~~~
    if (q == REGISTER) {
        scan_optional_equals();
    }
    else {
        scan_keyword("by"); // do nothing, optional "by"
    }
    arith_error = false;
    if (q < MULTIPLY) {
        // ~~~ Compute result of |REGISTER| or |ADVANCE|, put it in |cur_val|, 1238 ~~~
        if (p < GLUE_VAL) {
            if (p == INT_VAL) {
                scan_int();
            }
            else {
                scan_normal_dimen;
            }
            if (q == ADVANCE) {
                cur_val += eqtb[l].integer;
            }
        }
        else {
            scan_glue(p);
            if (q == ADVANCE) {
                // ~~~ Compute the sum of two glue specs, 1239 ~~~
                q = new_spec(cur_val);
                r = equiv(l);
                delete_glue_ref(cur_val);
                width(q) += width(r);
                if (stretch(q) == 0) {
                    stretch_order(q) = NORMAL;
                }
                if (stretch_order(q) == stretch_order(r)) {
                    stretch(q) += stretch(r);
                }
                else if (stretch_order(q) < stretch_order(r) && stretch(r) != 0) {
                    stretch(q) = stretch(r);
                    stretch_order(q) = stretch_order(r);
                }
                if (shrink(q) == 0) {
                    shrink_order(q) = NORMAL;
                }
                if (shrink_order(q) == shrink_order(r)) {
                    shrink(q) += shrink(r);
                }
                else if (shrink_order(q) < shrink_order(r) && shrink(r) != 0) {
                    shrink(q) = shrink(r);
                    shrink_order(q) = shrink_order(r);
                }
                cur_val = q;
                // ~~~ End section 1239 ~~~
            }
        }
        // ~~~ End section 1238 ~~~
    }
    else {
        // ~~~ Compute result of |MULTIPLY| or |DIVIDE|, put it in |cur_val|, 1240 ~~~
        scan_int();
        if (p < GLUE_VAL) {
            if (q == MULTIPLY) {
                if (p == INT_VAL) {
                    cur_val = mult_integers(eqtb[l].integer, cur_val);
                }
                else {
                    cur_val = nx_plus_y(eqtb[l].integer, cur_val, 0);
                }
            }
            else {
                cur_val = x_over_n(eqtb[l].integer, cur_val);
            }
        }
        else {
            s = equiv(l);
            r = new_spec(s);
            if (q == MULTIPLY) {
                width(r) = nx_plus_y(width(s), cur_val, 0);
                stretch(r) = nx_plus_y(stretch(s), cur_val, 0);
                shrink(r) = nx_plus_y(shrink(s), cur_val, 0);
            }
            else {
                width(r) = x_over_n(width(s), cur_val);
                stretch(r) = x_over_n(stretch(s), cur_val);
                shrink(r) = x_over_n(shrink(s), cur_val);
            }
            cur_val = r;
        }
        // ~~~ End section 1240 ~~~
    }
    if (arith_error) {
        print_err("Arithmetic overflow");
        help2("I can't carry out that multiplication or division,")
            ("since the result is out of range.");
        if (p >= GLUE_VAL) {
            delete_glue_ref(cur_val);
        }
        error();
        return;
    }
    if (p < GLUE_VAL) {
        word_define(l, cur_val);
    }
    else {
        trap_zero_glue();
        define(l, GLUE_REF, cur_val);
    }
}
// ~~~ End section 1236 ~~~

// ~~~ Section 1243 ~~~
void alter_aux() {
    halfword c; // |HMODE| or |VMODE|
    if (cur_chr != abs(mode)) {
        report_illegal_case();
    }
    else {
        c = cur_chr;
        scan_optional_equals();
        if (c == VMODE) {
            scan_normal_dimen;
            prev_depth = cur_val;
        }
        else {
            scan_int();
            if (cur_val <= 0 || cur_val > 32767) {
                print_err("Bad space factor");
                help1("I allow only values in the range 1..32767 here.");
                int_error(cur_val);
            }
            else {
                space_factor = cur_val;
            }
        }
    }
}
// ~~~ End section 1243 ~~~

// ~~~ Section 1244 ~~~
void alter_prev_graf() {
    int p; // index into |nest|
    nest[nest_ptr] = cur_list;
    p = nest_ptr;
    while (abs(nest[p].mode_field) != VMODE) {
        decr(p);
    }
    scan_optional_equals();
    scan_int();
    if (cur_val < 0) {
        print_err("Bad ");
        print_esc("prevgraf");
        help1("I allow only nonnegative values here.");
        int_error(cur_val);
    }
    else {
        nest[p].pg_field = cur_val;
        cur_list = nest[nest_ptr];
    }
}
// ~~~ End section 1244 ~~~

// ~~~ Section 1245 ~~~
void alter_page_so_far() {
    int c; // index into |page_so_far|
    c = cur_chr;
    scan_optional_equals();
    scan_normal_dimen;
    page_so_far[c] = cur_val;
}
// ~~~ End section 1245 ~~~

// ~~~ Section 1246 ~~~
void alter_integer() {
    int c; // 0 for \deadcycles, 1 for \insertpenalties
    c = cur_chr;
    scan_optional_equals();
    scan_int();
    if (c == 0) {
        dead_cycles = cur_val;
    }
    else {
        insert_penalties = cur_val;
    }
}
// ~~~ End section 1246 ~~~

// ~~~ Section 1247 ~~~
void alter_box_dimen() {
    small_number c; // |WIDTH_OFFSET| or |HEIGHT_OFFSET| or |DEPTH_OFFSET|
    eight_bits b; // box number
    c = cur_chr;
    scan_eight_bit_int();
    b = cur_val;
    scan_optional_equals();
    scan_normal_dimen;
    if (box(b) != null) {
        mem[box(b) + c].sc = cur_val;
    }
}
// ~~~ End section 1247 ~~~

// ~~~ Section 1257 ~~~
void new_font(small_number a) {
    pointer u;                   // user's font identifier
    scaled s;                    // stated "at" size, or negative of scaled magnification
    int f;                       // runs through existing fonts
    str_number t;                // name for the frozen font identifier
    int old_setting;             // holds |selector| setting
    str_number flushable_string; // string not yet referenced
    
    if (job_name == 0) {
        // avoid confusing `texput` with the font name
        open_log_file();
    }
    get_r_token();
    u = cur_cs;
    if (u >= HASH_BASE) {
        t = text(u);
    }
    else if (u >= SINGLE_BASE) {
        if (u == NULL_CS) {
            t = FONT_STRING; // "FONT"
        }
        else {
            t = u - SINGLE_BASE;
        }
    }
    else {
        old_setting = selector;
        selector = NEW_STRING;
        print("FONT");
        print_strnumber(u - ACTIVE_BASE);
        selector = old_setting;
        str_room(1);
        t = make_string();
    }
    define(u, SET_FONT, NULL_FONT);
    scan_optional_equals();
    scan_file_name();
    // ~~~ Scan the font size specification, 1258 ~~~
    name_in_progress = true; // this keeps |cur_name| from being changed
    if (scan_keyword("at")) {
        // ~~~ Put the (positive) 'at' size into |s|, 1259 ~~~
        scan_normal_dimen;
        s = cur_val;
        if (s <= 0 || s >= 0x8000000) {
            print_err("Improper `at' size (");
            print_scaled(s);
            print("pt), replaced by 10pt");
            help2("I can only handle fonts at positive sizes that are")
                ("less than 2048pt, so I've changed what you said to 10pt.");
            error();
            s = 10*UNITY;
        }
        // ~~~ End section 1259 ~~~
    }
    else if (scan_keyword("scaled")) {
        scan_int();
        s = -cur_val;
        if (cur_val <= 0 || cur_val > 32768) {
            print_err("Illegal magnification has been changed to 1000");
            help1("The magnification ratio must be between 1 and 32768.");
            int_error(cur_val);
            s = -1000;
        }
    }
    else {
        s = -1000;
    }
    name_in_progress = false;
    // ~~~ End section 1258 ~~~
    // ~~~ If this font has already been loaded, set |f| to the internal font number and |goto common_ending|, 1260 ~~~
    flushable_string = str_ptr - 1;
    for(f = FONT_BASE + 1; f <= font_ptr; f++) {
        if (str_eq_str(font_name[f], cur_name)
            && str_eq_str(font_area[f], cur_area))
        {
            if (cur_name == flushable_string) {
                flush_string;
                cur_name = font_name[f];
            }
            if (s > 0) {
                if (s == font_size[f]) {
                    goto common_ending;
                }
            }
            else if (font_size[f] == xn_over_d(font_dsize[f], -s, 1000)) {
                goto common_ending;
            }
        }
    }
    // ~~~ End section 1260 ~~~
    f = read_font_info(u, cur_name, cur_area, s);
common_ending:
    equiv(u) = f;
    eqtb[FONT_ID_BASE + f] = eqtb[u];
    font_id_text(f) = t;
}
// ~~~ End section 1257 ~~~

// ~~~ Section 1265 ~~~
void new_interaction() {
    print_ln();
    interaction = cur_chr;
    // ~~~ Initialize the print |selector| based on |interaction|, 75 ~~~
    if (interaction == BATCH_MODE) {
        selector = NO_PRINT;
    }
    else {
        selector = TERM_ONLY;
    }
    // ~~~ End section 75 ~~~
    if (log_opened) {
        selector += 2;
    }
}
// ~~~ End section 1265 ~~~
// ~~~ End section 1215 ~~~

void prefixed_command() {
    small_number a;         // accumulated prefix codes so far
    internal_font_number f; // identifies a font
    halfword j;             // index into a \parshape specification
    int k;                  // index into |font_info|
    pointer p, q;           // for temporary short - term use
    int n;                  // ditto
    bool e;                 // should a definition be expanded? or was \let not done?
    
    a = 0;
    while (cur_cmd == PREFIX) {
        if (!odd(a / cur_chr)) {
            a += cur_chr;
        }
        // ~~~ Get the next non-blank non-relax non-call token, 404 ~~~
        do {
            get_x_token();
        } while (cur_cmd == SPACER || cur_cmd == RELAX);
        // ~~~ End section 404 ~~~
        if (cur_cmd <= MAX_NON_PREFIXED_COMMAND) {
            // ~~~ Discard erroneous prefixes and |return|, 1212 ~~~
            print_err("You can't use a prefix with `");
            print_cmd_chr(cur_cmd, cur_chr);
            print_char('\'');
            help1("I'll pretend you didn't say \\long or \\outer or \\global.");
            back_error();
            return;
            // ~~~ End section 1212 ~~~
        }
    }
    // ~~~ Discard the prefixes \long and \outer if they are irrelevant, 1213 ~~~
    if (cur_cmd != DEF && a % 4 != 0) {
        print_err("You can't use `");
        print_esc("long");
        print("' or `");
        print_esc("outer");
        print("' with `");
        print_cmd_chr(cur_cmd, cur_chr);
        print_char('\'');
        help1("I'll pretend you didn't say \\long or \\outer here.");
        error();
    }
    // ~~~ End section 1213 ~~~
    // ~~~ Adjust for the setting of \globaldefs, 1214 ~~~
    if (global_defs != 0) {
        if (global_defs < 0) {
            if (global) {
                a -= 4;
            }
        }
        else if (!global) {
            a += 4;
        }
    }
    // ~~~ End section 1214 ~~~
    switch (cur_cmd) {
    // ~~~ Assignments, 1217 ~~~
    case SET_FONT:
        define(CUR_FONT_LOC, DATA, cur_chr);
        break;
    
    // ~~~ Section 1218 ~~~
    case DEF:
        if (odd(cur_chr)
            && !global
            && global_defs >= 0)
        {
            a += 4;
        }
        e = (cur_chr >= 2);
        get_r_token();
        p = cur_cs;
        q = scan_toks(true, e);
        define(p, CALL + (a % 4), def_ref);
        break;
    // ~~~ End section 1218 ~~~
    
    // ~~~ Section 1221 ~~~
    case LET:
        n = cur_chr;
        get_r_token();
        p = cur_cs;
        if (n == NORMAL) {
            do {
                get_token();
            } while (cur_cmd == SPACER);
            if (cur_tok == OTHER_TOKEN + '=') {
                get_token();
                if (cur_cmd == SPACER) {
                    get_token();
                }
            }
        }
        else {
            get_token();
            q = cur_tok;
            get_token();
            back_input();
            cur_tok = q;
            back_input(); // look ahead, then back up
        } // note that |back_input| doesn't affect |cur_cmd|, |cur_chr|
        if (cur_cmd >= CALL) {
            add_token_ref(cur_chr);
        }
        define(p, cur_cmd, cur_chr);
        break;
    // ~~~ End section 1221 ~~~
    
    // ~~~ Section 1224 ~~~
    case SHORTHAND_DEF:
        n = cur_chr;
        get_r_token();
        p = cur_cs;
        define(p, RELAX, 256);
        scan_optional_equals();
        switch (n) {
        case CHAR_DEF_CODE:
            scan_char_num();
            define(p, CHAR_GIVEN, cur_val);
            break;
      
        case MATH_CHAR_DEF_CODE:
            scan_fifteen_bit_int();
            define(p, MATH_GIVEN, cur_val);
            break;
      
        default:
            scan_eight_bit_int();
            switch (n) {
            case COUNT_DEF_CODE:
                define(p, ASSIGN_INT, COUNT_BASE + cur_val);
                break;
            case DIMEN_DEF_CODE:
                define(p, ASSIGN_DIMEN, SCALED_BASE + cur_val);
                break;
            case SKIP_DEF_CODE:
                define(p, ASSIGN_GLUE, SKIP_BASE + cur_val);
                break;
            case MU_SKIP_DEF_CODE:
                define(p, ASSIGN_MU_GLUE, MU_SKIP_BASE + cur_val);
                break;
            case TOKS_DEF_CODE:
                define(p, ASSIGN_TOKS, TOKS_BASE + cur_val);
            } // there are no other cases
        }
        break;
    // ~~~ End section 1224 ~~~
    
    // ~~~ Section 1225 ~~~
    case READ_TO_CS:
        scan_int();
        n = cur_val;
        if (!scan_keyword("to")) {
            print_err("Missing `to' inserted");
            help2("You should have said `\\read<number> to \\cs'.")
                ("I'm going to look for the \\cs now.");
            error();
        }
        get_r_token();
        p = cur_cs;
        read_toks(n, p);
        define(p, CALL, cur_val);
        break;
    // ~~~ End section 1225 ~~~
    
    // ~~~ Section 1226 ~~~
    case TOKS_REGISTER:
    case ASSIGN_TOKS:
        q = cur_cs;
        if (cur_cmd == TOKS_REGISTER) {
            scan_eight_bit_int();
            p = TOKS_BASE + cur_val;
        }
        else {
            p = cur_chr; // |p = EVERY_PAR_LOC| or |OUTPUT_ROUTINE_LOC| or...
        }
        scan_optional_equals();
        // ~~~ Get the next non-blank non-relax non-call token, 404 ~~~
        do {
            get_x_token();
        } while (cur_cmd == SPACER || cur_cmd == RELAX);
        // ~~~ End section 404 ~~~
        if (cur_cmd != LEFT_BRACE) {
            // ~~~ If the right-hand side is a token parameter or token register, finish the assignment and |goto done|, 1227 ~~~
            if (cur_cmd == TOKS_REGISTER) {
                scan_eight_bit_int();
                cur_cmd = ASSIGN_TOKS;
                cur_chr = TOKS_BASE + cur_val;
            }
            if (cur_cmd == ASSIGN_TOKS) {
                q = equiv(cur_chr);
                if (q == null) {
                    define(p, UNDEFINED_CS, null);
                }
                else {
                    add_token_ref(q);
                    define(p, CALL, q);
                }
                goto done;
            }
            // ~~~ End section 1227 ~~~
        }
        back_input();
        cur_cs = q;
        q = scan_toks(false, false);
        if (link(def_ref) == null) {
             // empty list: revert to the default
            define(p, UNDEFINED_CS, null);
            free_avail(def_ref);
        }
        else {
            if (p == OUTPUT_ROUTINE_LOC) {
                // enclose in curlies
                link(q) = get_avail();
                q = link(q);
                info(q) = RIGHT_BRACE_TOKEN + '}';
                q = get_avail();
                info(q) = LEFT_BRACE_TOKEN + '{';
                link(q) = link(def_ref);
                link(def_ref) = q;
            }
            define(p, CALL, def_ref);
        }
        break;
    // ~~~ End section 1226 ~~~
    
    // ~~~ Section 1228 ~~~
    case ASSIGN_INT:
        p = cur_chr;
        scan_optional_equals();
        scan_int();
        word_define(p, cur_val);
        break;
    
    case ASSIGN_DIMEN:
        p = cur_chr;
        scan_optional_equals();
        scan_normal_dimen;
        word_define(p, cur_val);
        break;
    
    case ASSIGN_GLUE:
    case ASSIGN_MU_GLUE:
        p = cur_chr;
        n = cur_cmd;
        scan_optional_equals();
        if (n == ASSIGN_MU_GLUE) {
            scan_glue(MU_VAL);
        }
        else {
            scan_glue(GLUE_VAL);
        }
        trap_zero_glue();
        define(p, GLUE_REF, cur_val);
        break;
    // ~~~ End section 1228 ~~~
    
    // ~~~ Section 1232 ~~~
    case DEF_CODE:
        // ~~~ Let |n| be the largest legal code value, based on |cur_chr|, 1233 ~~~
        if (cur_chr == CAT_CODE_BASE) {
            n = MAX_CHAR_CODE;
        }
        else if (cur_chr == MATH_CODE_BASE) {
            n = 0x8000;
        }
        else if (cur_chr == SF_CODE_BASE) {
            n = 0x7fff;
        }
        else if (cur_chr == DEL_CODE_BASE) {
            n = 0xffffff;
        }
        else {
            n = 255;
        }
        // ~~~ End section 1233 ~~~
        p = cur_chr;
        scan_char_num();
        p += cur_val;
        scan_optional_equals();
        scan_int();
        if ((cur_val < 0 && p < DEL_CODE_BASE) || cur_val > n) {
            print_err("Invalid code (");
            print_int(cur_val);
            if (p < DEL_CODE_BASE) {
                print("), should be in the range 0..");
            }
            else {
                print("), should be at most ");
            }
            print_int(n);
            help1("I'm going to use 0 instead of that illegal code value.");
            error();
            cur_val = 0;
        }
        if (p < MATH_CODE_BASE) {
            define(p, DATA, cur_val);
        }
        else if (p < DEL_CODE_BASE) {
            define(p, DATA, hi(cur_val));
        }
        else {
            word_define(p, cur_val);
        }
        break;
    // ~~~ End section 1232 ~~~
    
    // ~~~ Section 1234 ~~~
    case DEF_FAMILY:
        p = cur_chr;
        scan_four_bit_int();
        p += cur_val;
        scan_optional_equals();
        scan_font_ident();
        define(p, DATA, cur_val);
        break;
    // ~~~ End section 1234 ~~~
    
    // ~~~ Section 1235 ~~~
    case REGISTER:
    case ADVANCE:
    case MULTIPLY:
    case DIVIDE:
        do_register_command(a);
        break;
    // ~~~ End section 1235 ~~~
    
    // ~~~ Section 1241 ~~~
    case SET_BOX:
        scan_eight_bit_int();
        if (global) {
            n = 256 + cur_val;
        }
        else {
            n = cur_val;
        }
        scan_optional_equals();
        if (set_box_allowed) {
            scan_box(BOX_FLAG + n);
        }
        else {
            print_err("Improper ");
            print_esc("setbox");
            help2("Sorry, \\setbox is not allowed after \\halign in a display,")
                ("or between \\accent and an accented character.");
            error();
        }
        break;
    // ~~~ End section 1241 ~~~
    
    // ~~~ Section 1242 ~~~
    case SET_AUX:
        alter_aux();
        break;
    
    case SET_PREV_GRAF:
        alter_prev_graf();
        break;
    
    case SET_PAGE_DIMEN:
        alter_page_so_far();
        break;
    
    case SET_PAGE_INT:
        alter_integer();
        break;
    
    case SET_BOX_DIMEN:
        alter_box_dimen();
        break;
    // ~~~ End section 1242 ~~~
    
    // ~~~ Section 1248 ~~~
    case SET_SHAPE:
        scan_optional_equals();
        scan_int();
        n = cur_val;
        if (n <= 0) {
            p = null;
        }
        else {
            p = get_node(2*n + 1);
            info(p) = n;
            for(j = 1; j <= n; j++) {
                scan_normal_dimen;
                mem[p + 2*j - 1].sc = cur_val; // indentation
                scan_normal_dimen;
                mem[p + 2*j].sc = cur_val; // width
            }
        }
        define(PAR_SHAPE_LOC, SHAPE_REF, p);
        break;
    // ~~~ End section 1248 ~~~
    
    // ~~~ Section 1252 ~~~
    case HYPH_DATA:
        if (cur_chr == 1) {
#ifdef INIT
            new_patterns();
            goto done;
#endif
            print_err("Patterns can be loaded only by INITEX");
            help0;
            error();
            do {
                get_token();
            } while (cur_cmd != RIGHT_BRACE); // flush the patterns
            return;
        }
        else {
            new_hyph_exceptions();
            goto done;
        }
    // ~~~ End section 1252 ~~~
    
    // ~~~ Section 1253 ~~~
    case ASSIGN_FONT_DIMEN:
        find_font_dimen(true);
        k = cur_val;
        scan_optional_equals();
        scan_normal_dimen;
        font_info[k].sc = cur_val;
        break;
    
    case ASSIGN_FONT_INT:
        n = cur_chr;
        scan_font_ident();
        f = cur_val;
        scan_optional_equals();
        scan_int();
        if (n == 0) {
            hyphen_char[f] = cur_val;
        }
        else {
            skew_char[f] = cur_val;
        }
        break;
    // ~~~ End section 1253 ~~~
    
    // ~~~ Section 1256 ~~~
    case DEF_FONT:
        new_font(a);
        break;
    // ~~~ End section 1256 ~~~
    
    // ~~~ Section 1264 ~~~
    case SET_INTERACTION:
        new_interaction();
        break;
    // ~~~ End section 1264 ~~~
    // ~~~ End section 1217 ~~~
    
    default:
        confusion("prefix");
    }
done:
    // ~~~ Insert a token saved by \afterassignment, if any, 1269 ~~~
    if (after_token != 0) {
        cur_tok = after_token;
        back_input();
        after_token = 0;
    }
    // ~~~ End section 1269 ~~~
}
// ~~~ End section 1211 ~~~

// ~~~ Section 1270 ~~~
void do_assignments() {
    while(true) {
        // ~~~ Get the next non-blank non-relax non-call token, 404 ~~~
        do {
            get_x_token();
        } while (cur_cmd == SPACER || cur_cmd == RELAX);
        // ~~~ End section 404 ~~~
        if (cur_cmd <= MAX_NON_PREFIXED_COMMAND) {
            return;
        }
        set_box_allowed = false;
        prefixed_command();
        set_box_allowed = true;
    }
}
// ~~~ End section 1270 ~~~

// ~~~ Section 1275 ~~~
void open_or_close_in() {
    int c; // 1 for \openin, 0 for \closein
    int n; // stream number
    c = cur_chr;
    scan_four_bit_int();
    n = cur_val;
    if (read_open[n] != CLOSED) {
        a_close(read_file[n]);
        read_open[n] = CLOSED;
    }
    if (c != 0) {
        scan_optional_equals();
        scan_file_name();
        if (cur_ext == EMPTY_STRING) {
            cur_ext = TEX_EXT; // ".tex"
        }
        pack_cur_name;
        if (a_open_in(&read_file[n])) {
            read_open[n] = JUST_OPEN;
        }
    }
}
// ~~~ End section 1275 ~~~

// ~~~ Section 1279 ~~~
void issue_message() {
    int old_setting; // holds |selector| setting
    int c;           // identifies \message and \errmessage
    str_number s;    // the message
    
    c = cur_chr;
    link(GARBAGE) = scan_toks(false, true);
    old_setting = selector;
    selector = NEW_STRING;
    token_show(def_ref);
    selector = old_setting;
    flush_list(def_ref);
    str_room(1);
    s = make_string();
    if (c == 0) {
        // ~~~ Print string |s| on the terminal, 1280 ~~~
        if (term_offset + length(s) > MAX_PRINT_LINE - 2) {
            print_ln();
        }
        else if (term_offset > 0 || file_offset > 0 ) {
            print_char(' ');
        }
        slow_print(s);
        update_terminal;
        // ~~~ End section 1280 ~~~
    }
    else {
        // ~~~ Print string |s| as an error message, 1283 ~~~
        print_err("");
        slow_print(s);
        if (err_help != null) {
            use_err_help = true;
        }
        else if (long_help_seen) {
            help1("(That was another \\errmessage.)");
        }
        else {
            if (interaction < ERROR_STOP_MODE) {
                long_help_seen = true;
            }
            help4("This error message was generated by an \\errmessage")
                ("command, so I can't give any explicit help.")
                ("Pretend that you're Hercule Poirot: Examine all clues,")
                ("and deduce the truth by order and method.");
        }
        error();
        use_err_help = false;
        // ~~~ End section 1283 ~~~
    }
    flush_string;
}
// ~~~ End section 1279 ~~~

// ~~~ Section 1288 ~~~
void shift_case() {
    pointer b;    // |lc_code_base| or |uc_code_base|
    pointer p;    // runs through the token list
    halfword t;   // token
    eight_bits c; // character code
    
    b = cur_chr;
    p = scan_toks(false, false);
    p = link(def_ref);
    while (p != null) {
        // ~~~ Change the case of the token in |p|, if a change is appropriate, 1289 ~~~
        t = info(p);
        if (t < CS_TOKEN_FLAG + SINGLE_BASE) {
            c = t % 256;
            if (equiv(b + c) != 0) {
                info(p) = t - c + equiv(b + c);
            }
        }
        // ~~~ End section 1289 ~~~
        p = link(p);
    }
    back_list(link(def_ref));
    free_avail(def_ref); // omit reference count
}
// ~~~ End section 1288 ~~~
