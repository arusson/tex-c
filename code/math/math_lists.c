// ~~~ Section 1136 ~~~
// ~~~ Start file |math_lists.c|, 1382 ~~~
#include "arithmetic.h"
#include "breaker.h"
#include "builder.h"
#include "font_metric.h"
#include "parser.h"
#include "texmath.h"
// ~~~ End section 1382 ~~~

void push_math(int c) {
    push_nest();
    mode = -MMODE;
    incompleat_noad = null;
    new_save_level(c);
}
// ~~~ End section 1136 ~~~

// ~~~ Section 1138 ~~~
void init_math() {
    scaled w;               // new or partial |pre_display_size|
    scaled l = 0;           // new |display_width|
    scaled s = 0;           // new |display_indent|
    pointer p;              // current node when calculating |pre_display_size|
    pointer q;              // glue specification when calculating |pre_display_size|
    internal_font_number f; // font in current |CHAR_NODE|
    int n;                  // scope of paragraph shape specification
    scaled v;               // |w| plus possible glue amount
    scaled d;               // increment to |v|
    
    get_token(); // |get_x_token| would fail on \ifmmode!
    if (cur_cmd == MATH_SHIFT && mode > 0) {
        // ~~~ Go into display math mode, 1145 ~~~
        if (head == tail) {
            // '\noindent$$' or '$$ $$'
            pop_nest();
            w = -MAX_DIMEN;
        }
        else {
            line_break(display_widow_penalty);
            // ~~~ Calculate the natural width, |w|, by which the characters of the final line extend to the right of the reference point, plus two ems; or set |w = MAX_DIMEN| if the non-blank information on that line is affected by stretching or shrinking, 1146 ~~~
            v = shift_amount(just_box) + 2 * quad(cur_font);
            w = -MAX_DIMEN;
            p = list_ptr(just_box);
            while (p != null) {
                // ~~~ Let |d| be the natural width of node |p|; if the node is "visible," |goto found|; if the node is glue that stretches or shrinks, set |v = MAX_DIMEN|, 1147 ~~~
reswitch:
                if (is_char_node(p)) {
                    f = font(p);
                    d = char_width(f, char_info(f, character(p)));
                    goto found;
                }
                
                switch (type(p)) {
                case HLIST_NODE:
                case VLIST_NODE:
                case RULE_NODE:
                    d = width(p);
                    goto found;
                
                case LIGATURE_NODE:
                    // ~~~ Make node |p| look like a |CHAR_NODE| and |goto reswitch|, 652 ~~~
                    mem[LIG_TRICK] = mem[lig_char(p)];
                    link(LIG_TRICK) = link(p);
                    p = LIG_TRICK;
                    goto reswitch;
                    // ~~~ End section 652 ~~~
                
                case KERN_NODE:
                case MATH_NODE:
                    d = width(p);
                    break;
                
                case GLUE_NODE:
                    // ~~~ Let |d| be the natural width of this glue; if stretching or shrinking, set |v = MAX_DIMEN|; |goto found| in the case of leaders, 1148 ~~~
                    q = glue_ptr(p);
                    d = width(q);
                    if (glue_sign(just_box) == STRETCHING) {
                        if (glue_order(just_box) == stretch_order(q) && stretch(q) != 0) {
                            v = MAX_DIMEN;
                        }
                    }
                    else if (glue_sign(just_box) == SHRINKING) {
                        if (glue_order(just_box) == shrink_order(q) && shrink(q) != 0) {
                            v = MAX_DIMEN;
                        }
                    }
                    if (subtype(p) >= A_LEADERS) {
                        goto found;
                    }
                    // ~~~ End section 1148 ~~~
                    break;
                
                case WHATSIT_NODE:
                    // ~~~ Let |d| be the width of the whatsit |p|, 1361 ~~~
                    d = 0;
                    // ~~~ End section 1361 ~~~
                    break;
                
                default:
                    d = 0;
                }
                // ~~~ End section 1147 ~~~
            
                if (v < MAX_DIMEN) {
                    v += d;
                }
                goto not_found;
found:
                if (v < MAX_DIMEN) {
                    v += d;
                    w = v;
                }
                else {
                    w = MAX_DIMEN;
                    break; // goto done
                }
not_found:
                p = link(p);
            }
            // done:
            // ~~~ End section 1146 ~~~
        }
        // now we are in vertical mode, working on the list that will contain the display
        
        // ~~~ Calculate the length, |l|, and the shift amount, |s|, of the display lines, 1149 ~~~
        if (par_shape_ptr == null) {
            if (hang_indent != 0) {
                if ((hang_after >= 0 && prev_graf + 2 > hang_after)
                    || prev_graf + 1 < -hang_after)
                {
                    l = hsize - abs(hang_indent);
                    if (hang_indent > 0) {
                        s = hang_indent;
                    }
                    else {
                        s = 0;
                    }
                }
            }
            else {
                l = hsize;
                s = 0;
            }
        }
        else {
            n = info(par_shape_ptr);
            if (prev_graf + 2 >= n) {
                p = par_shape_ptr + 2 * n;
            }
            else {
                p = par_shape_ptr + 2 * (prev_graf + 2);
            }
            s = mem[p - 1].sc;
            l = mem[p].sc;
        }
        // ~~~ End section 1149 ~~~
        push_math(MATH_SHIFT_GROUP);
        mode = MMODE;
        eq_word_define(INT_BASE + CUR_FAM_CODE, -1);
        eq_word_define(DIMEN_BASE + PRE_DISPLAY_SIZE_CODE, w);
        eq_word_define(DIMEN_BASE + DISPLAY_WIDTH_CODE, l);
        eq_word_define(DIMEN_BASE + DISPLAY_INDENT_CODE, s);
        if (every_display != null) {
            begin_token_list(every_display, EVERY_DISPLAY_TEXT);
        }
        if (nest_ptr == 1) {
            build_page();
        }
        // ~~~ End section 1145 ~~~
    }
    else {
        back_input();
        // ~~~ Go into ordinary math mode, 1139 ~~~
        push_math(MATH_SHIFT_GROUP);
        eq_word_define(INT_BASE + CUR_FAM_CODE, -1);
        if (every_math != null) {
            begin_token_list(every_math, EVERY_MATH_TEXT);
        }
        // ~~~ End section 1139 ~~~
    }
}
// ~~~ End section 1138 ~~~

// ~~~ Section 1142 ~~~
void start_eq_no() {
    saved(0) = cur_chr;
    incr(save_ptr);
    // ~~~ Go into ordinary math mode, 1139 ~~~
    push_math(MATH_SHIFT_GROUP);
    eq_word_define(INT_BASE + CUR_FAM_CODE, -1);
    if (every_math != null) {
        begin_token_list(every_math, EVERY_MATH_TEXT);
    }
    // ~~~ End section 1139 ~~~
}
// ~~~ End section 1142 ~~~

// ~~~ Section 1151 ~~~
void scan_math(pointer p) {
    int c; // math character code

restart:
    // ~~~ Get the next non-blank non-relax non-call token, 404 ~~~
    do {
        get_x_token();
    } while (cur_cmd == SPACER || cur_cmd == RELAX);
    // ~~~ End section 404 ~~~

reswitch:
    switch (cur_cmd) {
    case LETTER:
    case OTHER_CHAR:
    case CHAR_GIVEN:
        c = ho(math_code(cur_chr));
        if (c == 0x8000) {
            // ~~~ Treat |cur_chr| as an active character, 1152 ~~~
            cur_cs = cur_chr + ACTIVE_BASE;
            cur_cmd = eq_type(cur_cs);
            cur_chr = equiv(cur_cs);
            x_token();
            back_input();
            // ~~~ End section 1152 ~~~
            goto restart;
        }
        break;
    
    case CHAR_NUM:
        scan_char_num();
        cur_chr = cur_val;
        cur_cmd = CHAR_GIVEN;
        goto reswitch;
    
    case MATH_CHAR_NUM:
        scan_fifteen_bit_int();
        c = cur_val;
        break;
    
    case MATH_GIVEN:
        c = cur_chr;
        break;
    
    case DELIM_NUM:
        scan_twenty_seven_bit_int();
        c = cur_val / 0x1000;
        break;
    
    default:
        // ~~~ Scan a subformula enclosed in braces and |return|, 1153 ~~~
        back_input();
        scan_left_brace();
        saved(0) = p;
        incr(save_ptr);
        push_math(MATH_GROUP);
        return;
        // ~~~ End section 1153 ~~~
    }
    math_type(p) = MATH_CHAR;
    character(p) = c % 256;
    if (c >= VAR_CODE && fam_in_range) {
        fam(p) = cur_fam;
    }
    else {
        fam(p) = (c / 256) % 16;
    }
}
// ~~~ End section 1151 ~~~

// ~~~ Section 1155 ~~~
void set_math_char(int c) {
    pointer p; // the new noad
    if (c >= 0x8000) {
        // ~~~ Treat |cur_chr| as an active character, 1152 ~~~
        cur_cs = cur_chr + ACTIVE_BASE;
        cur_cmd = eq_type(cur_cs);
        cur_chr = equiv(cur_cs);
        x_token();
        back_input();
        // ~~~ End section 1152 ~~~
    }
    else {
        p = new_noad();
        math_type(nucleus(p)) = MATH_CHAR;
        character(nucleus(p)) = c % 256;
        fam(nucleus(p)) = (c / 256) % 16;
        if (c >= VAR_CODE) {
            if (fam_in_range) {
                fam(nucleus(p)) = cur_fam;
            }
            type(p) = ORD_NOAD;
        }
        else {
            type(p) = ORD_NOAD + (c / 0x1000);
        }
        link(tail) = p;
        tail = p;
    }
}
// ~~~ End section 1155 ~~~

// ~~~ Section 1159 ~~~
void math_limit_switch() {
    if (head != tail && type(tail) == OP_NOAD) {
        subtype(tail) = cur_chr;
        return;
    }
    print_err("Limit controls must follow a math operator");
    help1("I'm ignoring this misplaced \\limits or \\nolimits command.");
    error();
}
// ~~~ End section 1159 ~~~

// ~~~ Section 1160 ~~~
void scan_delimiter(pointer p, bool r) {
    if (r) {
        scan_twenty_seven_bit_int();
    }
    else {
        // ~~~ Get the next non-blank non-relax non-call token, 404 ~~~
        do {
            get_x_token();
        } while (cur_cmd == SPACER || cur_cmd == RELAX);
        // ~~~ End section 404 ~~~
        switch (cur_cmd) {
        case LETTER:
        case OTHER_CHAR:
            cur_val = del_code(cur_chr);
            break;
        
        case DELIM_NUM:
            scan_twenty_seven_bit_int();
            break;
        
        default:
            cur_val = -1;
        }
    }
    if (cur_val < 0) {
        // ~~~ Report that an invalid delimiter code is being changed to null; set |cur_val = 0|, 1161 ~~~
        print_err("Missing delimiter (. inserted)");
        help6("I was expecting to see something like `(' or `\\{' or")
            ("`\\}' here. If you typed, e.g., `{' instead of `\\{', you")
            ("should probably delete the `{' by typing `1' now, so that")
            ("braces don't get unbalanced. Otherwise just proceed.")
            ("Acceptable delimiters are characters whose \\delcode is")
            ("nonnegative, or you can use `\\delimiter <delimiter code>'.");
        back_error();
        cur_val = 0;
        // ~~~ End section 1161 ~~~
    }
    small_fam(p) = (cur_val / 0x100000) % 16;
    small_char(p) = (cur_val / 0x1000) % 256;
    large_fam(p) = (cur_val / 256) % 16;
    large_char(p) = cur_val % 256;
}
// ~~~ End section 1160 ~~~

// ~~~ Section 1163 ~~~
void math_radical() {
    tail_append(get_node(RADICAL_NOAD_SIZE));
    type(tail) = RADICAL_NOAD;
    subtype(tail) = NORMAL;
    mem[nucleus(tail)] = empty_field;
    mem[subscr(tail)] = empty_field;
    mem[supscr(tail)] = empty_field;
    scan_delimiter(left_delimiter(tail), true);
    scan_math(nucleus(tail));
}
// ~~~ End section 1163 ~~~

// ~~~ Section 1165 ~~~
void math_ac() {
    if (cur_cmd == ACCENT) {
        // ~~~ Complain that the user should have said \mathaccent, 1166 ~~~
        print_err("Please use ");
        print_esc("mathaccent");
        print(" for accents in math mode");
        help2("I'm changing \\accent to \\mathaccent here; wish me luck.")
            ("(Accents are not the same in formulas as they are in text.)");
        error();
        // ~~~ End section 1166 ~~~
    }
    tail_append(get_node(ACCENT_NOAD_SIZE));
    type(tail) = ACCENT_NOAD;
    subtype(tail) = NORMAL;
    mem[nucleus(tail)] = empty_field;
    mem[subscr(tail)] = empty_field;
    mem[supscr(tail)] = empty_field;
    math_type(accent_chr(tail)) = MATH_CHAR;
    scan_fifteen_bit_int();
    character(accent_chr(tail)) = cur_val % 256;
    if (cur_val >= VAR_CODE && fam_in_range) {
        fam(accent_chr(tail)) = cur_fam;
    }
    else {
        fam(accent_chr(tail)) = (cur_val / 256) % 16;
    }
    scan_math(nucleus(tail));
}
// ~~~ End section 1165 ~~~

// ~~~ Section 1172 ~~~
void append_choices() {
    tail_append(new_choice());
    incr(save_ptr);
    saved(-1) = 0;
    push_math(MATH_CHOICE_GROUP);
    scan_left_brace();
}
// ~~~ End section 1172 ~~~

// ~~~ Section 1174 ~~~
// ~~~ Declare the function called |fin_mlist|, 1184 ~~~
pointer fin_mlist(pointer p) {
    pointer q; // the mlist to return
    if (incompleat_noad != null) {
        // ~~~ Compleat the incompleat noad, 1185 ~~~
        math_type(denominator(incompleat_noad)) = SUB_MLIST;
        info(denominator(incompleat_noad)) = link(head);
        if (p == null) {
            q = incompleat_noad;
        }
        else {
            q = info(numerator(incompleat_noad));
            if (type(q) != LEFT_NOAD) {
                confusion("right");
            }
            info(numerator(incompleat_noad)) = link(q);
            link(q) = incompleat_noad;
            link(incompleat_noad) = p;
        }
        // ~~~ End section 1185 ~~~
    }
    else {
        link(tail) = p;
        q = link(head);
    }
    pop_nest();
    return q;
}
// ~~~ End section 1184 ~~~

void build_choices() {
    pointer p; // the current mlist
    unsave();
    p = fin_mlist(null);
    switch (saved(-1)) {
    case 0:
        display_mlist(tail) = p;
        break;
    
    case 1:
        text_mlist(tail) = p;
        break;
    
    case 2:
        script_mlist(tail) = p;
        break;
    
    case 3:
        script_script_mlist(tail) = p;
        decr(save_ptr);
        return;
    } // there are no other cases
    incr(saved(-1));
    push_math(MATH_CHOICE_GROUP);
    scan_left_brace();
}
// ~~~ End section 1174 ~~~

// ~~~ Section 1176 ~~~
void sub_sup() {
    small_number t; // type of previous sub/superscript
    pointer p;      // field to be filled by |scan_math|
    t = EMPTY;
    p = null;
    if (tail != head && scripts_allowed(tail)) {
        p = supscr(tail) + cur_cmd - SUP_MARK; // |supscr| or |subscr|
        t = math_type(p);
    }
    if (p == null || t != EMPTY) {
        // ~~~ Insert a dummy noad to be sub/superscripted, 1177 ~~~
        tail_append(new_noad());
        p = supscr(tail) + cur_cmd - SUP_MARK; // |supscr| or |subscr|
        if (t != EMPTY) {
            if (cur_cmd == SUP_MARK) {
                print_err("Double superscript");
                help1("I treat `x^1^2' essentially like `x^1{}^2'.");
            }
            else {
                print_err("Double subscript");
                help1("I treat `x_1_2' essentially like `x_1{}_2'.");
            }
            error();
        }
        // ~~~ End section 1177 ~~~
    }
    scan_math(p);
}
// ~~~ End section 1176 ~~~

// ~~~ Section 1181 ~~~
void math_fraction() {
    small_number c; // the type of generalized fraction we are scanning
    c = cur_chr;
    if (incompleat_noad != null) {
        // ~~~ Ignore the fraction operation and complain about this ambiguous case, 1183 ~~~
        if (c >= DELIMITED_CODE) {
            scan_delimiter(GARBAGE, false);
            scan_delimiter(GARBAGE, false);
        }
        if (c % DELIMITED_CODE == ABOVE_CODE) {
            scan_normal_dimen;
        }
        print_err("Ambiguous; you need another { and }");
        help3("I'm ignoring this fraction specification, since I don't")
            ("know whether a construction like `x \\over y \\over z'")
            ("means `{x \\over y} \\over z' or `x \\over {y \\over z}'.");
        error();
        // ~~~ End section 1183 ~~~
    }
    else {
        incompleat_noad = get_node(FRACTION_NOAD_SIZE);
        type(incompleat_noad) = FRACTION_NOAD;
        subtype(incompleat_noad) = NORMAL;
        math_type(numerator(incompleat_noad)) = SUB_MLIST;
        info(numerator(incompleat_noad)) = link(head);
        mem[denominator(incompleat_noad)] = empty_field;
        mem[left_delimiter(incompleat_noad)] = null_delimiter;
        mem[right_delimiter(incompleat_noad)] = null_delimiter;
        link(head) = null;
        tail = head;
        // ~~~ Use code |c| to distinguish between generalized fractions, 1182 ~~~
        if (c >= DELIMITED_CODE) {
            scan_delimiter(left_delimiter(incompleat_noad), false);
            scan_delimiter(right_delimiter(incompleat_noad), false);
        }
        switch (c % DELIMITED_CODE) {
        case ABOVE_CODE:
            scan_normal_dimen;
            thickness(incompleat_noad) = cur_val;
            break;
        
        case OVER_CODE:
            thickness(incompleat_noad) = DEFAULT_CODE;
            break;
        
        case ATOP_CODE:
            thickness(incompleat_noad) = 0;
        } // there are no other cases
        // ~~~ End section 1182 ~~~
    }
}
// ~~~ End section 1181 ~~~

// ~~~ Section 1191 ~~~
void math_left_right() {
    small_number t; // |LEFT_NOAD| or |RIGHT_NOAD|
    pointer p;      // new noad
    t = cur_chr;
    if (t == RIGHT_NOAD && cur_group != MATH_LEFT_GROUP) {
        // ~~~ Try to recover from mismatched \right, 1192 ~~~
        if (cur_group == MATH_SHIFT_GROUP) {
            scan_delimiter(GARBAGE, false);
            print_err("Extra ");
            print_esc("right");
            help1("I'm ignoring a \\right that had no matching \\left.");
            error();
        }
        else {
            off_save();
        }
        // ~~~ End section 1192 ~~~
    }
    else {
        p = new_noad();
        type(p) = t;
        scan_delimiter(delimiter(p), false);
        if (t == LEFT_NOAD) {
            push_math(MATH_LEFT_GROUP);
            link(head) = p;
            tail = p;
        }
        else {
            p = fin_mlist(p);
            unsave(); // end of |MATH_LEFT_GROUP|
            tail_append(new_noad());
            type(tail) = INNER_NOAD;
            math_type(nucleus(tail)) = SUB_MLIST;
            info(nucleus(tail)) = p;
        }
    }
}
// ~~~ End section 1191 ~~~

// ~~~ Section 1194 ~~~
void after_math() {
    bool l;      // '\leqno' instead of '\eqno'
    bool danger; // not enough symbol fonts are present
    int m;       // |MMODE| or |-MMODE|
    pointer p;   // the formula
    pointer a;   // box containing equation number
    // ~~~ Local variables for finishing a displayed formula, 1198 ~~~
    pointer b;           // box containing the equation
    scaled w;            // width of the equation
    scaled z;            // width of the line
    scaled e;            // width of equation number
    scaled q;            // width of equation number plus space to separate from equation
    scaled d;            // displacement of equation in the line
    scaled s;            // move the line right this much
    small_number g1, g2; // glue parameter codes for before and after
    pointer r;           // kern node used to position the display
    pointer t;           // tail of adjustment list
    // ~~~ End section 1198 ~~~

    danger = false;
    // ~~~ Check that the necessary fonts for math symbols are present; if not, flush the current math lists and set |danger = true|, 1195 ~~~
    if (font_params[fam_fnt(2 + TEXT_SIZE)] < TOTAL_MATHSY_PARAMS
        || font_params[fam_fnt(2 + SCRIPT_SIZE)] < TOTAL_MATHSY_PARAMS
        || font_params[fam_fnt(2 + SCRIPT_SCRIPT_SIZE)] < TOTAL_MATHSY_PARAMS)
    {
        print_err("Math formula deleted: Insufficient symbol fonts");
        help3("Sorry, but I can't typeset math unless \\textfont 2")
            ("and \\scriptfont 2 and \\scriptscriptfont 2 have all")
            ("the \\fontdimen values needed in math symbol fonts.");
        error();
        flush_math();
        danger = true;
    }
    else if (font_params[fam_fnt(3 + TEXT_SIZE)] < TOTAL_MATHEX_PARAMS
        || font_params[fam_fnt(3 + SCRIPT_SIZE)] < TOTAL_MATHEX_PARAMS
        || font_params[fam_fnt(3 + SCRIPT_SCRIPT_SIZE)] < TOTAL_MATHEX_PARAMS)
    {
        print_err("Math formula deleted: Insufficient extension fonts");
        help3("Sorry, but I can't typeset math unless \\textfont 3")
            ("and \\scriptfont 3 and \\scriptscriptfont 3 have all")
            ("the \\fontdimen values needed in math extension fonts.");
        error();
        flush_math();
        danger = true;
    }
    // ~~~ End section 1195 ~~~
    m = mode;
    l = false;
    p = fin_mlist(null); // this pops the nest
    if (mode == -m) {
        // end of equation number
        // ~~~ Check that another $ follows, 1197 ~~~
        get_x_token();
        if (cur_cmd != MATH_SHIFT) {
            print_err("Display math should end with $$");
            help2("The `$' that I just saw supposedly matches a previous `$$'.")
                ("So I shall assume that you typed `$$' both times.");
            back_error();
        }
        // ~~~ End section 1197 ~~~
        cur_mlist = p;
        cur_style = TEXT_STYLE;
        mlist_penalties = false;
        mlist_to_hlist();
        a = hpack(link(TEMP_HEAD), NATURAL);
        unsave();
        decr(save_ptr); // now |cur_group = MATH_SHIFT_GROUP|
        if (saved(0) == 1) {
            l = true;
        }
        danger = false;
        // ~~~ Check that the necessary fonts for math symbols are present; if not, flush the current math lists and set |danger = true|, 1195 ~~~
        if (font_params[fam_fnt(2 + TEXT_SIZE)] < TOTAL_MATHSY_PARAMS
            || font_params[fam_fnt(2 + SCRIPT_SIZE)] < TOTAL_MATHSY_PARAMS
            || font_params[fam_fnt(2 + SCRIPT_SCRIPT_SIZE)] < TOTAL_MATHSY_PARAMS)
        {
            print_err("Math formula deleted: Insufficient symbol fonts");
            help3("Sorry, but I can't typeset math unless \\textfont 2")
                ("and \\scriptfont 2 and \\scriptscriptfont 2 have all")
                ("the \\fontdimen values needed in math symbol fonts.");
            error();
            flush_math();
            danger = true;
        }
        else if (font_params[fam_fnt(3 + TEXT_SIZE)] < TOTAL_MATHEX_PARAMS
            || font_params[fam_fnt(3 + SCRIPT_SIZE)] < TOTAL_MATHEX_PARAMS
            || font_params[fam_fnt(3 + SCRIPT_SCRIPT_SIZE)] < TOTAL_MATHEX_PARAMS)
        {
            print_err("Math formula deleted: Insufficient extension fonts");
            help3("Sorry, but I can't typeset math unless \\textfont 3")
                ("and \\scriptfont 3 and \\scriptscriptfont 3 have all")
                ("the \\fontdimen values needed in math extension fonts.");
            error();
            flush_math();
            danger = true;
        }
        // ~~~ End section 1195 ~~~
        m = mode;
        p = fin_mlist(null);
    }
    else {
        a = null;
    }
    if (m < 0) {
        // ~~~ Finish math in text, 1196 ~~~
        tail_append(new_math(math_surround, BEFORE));
        cur_mlist = p;
        cur_style = TEXT_STYLE;
        mlist_penalties = (mode > 0);
        mlist_to_hlist();
        link(tail) = link(TEMP_HEAD);
        while (link(tail) != null) {
            tail = link(tail);
        }
        tail_append(new_math(math_surround, AFTER));
        space_factor = 1000;
        unsave();
        // ~~~ End section 1196 ~~~
    }
    else {
        if (a == null) {
            // ~~~ Check that another $ follows, 1197 ~~~
            get_x_token();
            if (cur_cmd != MATH_SHIFT) {
                print_err("Display math should end with $$");
                help2("The `$' that I just saw supposedly matches a previous `$$'.")
                    ("So I shall assume that you typed `$$' both times.");
                back_error();
            }
            // ~~~ End section 1197 ~~~
        }
        // ~~~ Finish displayed math, 1199 ~~~
        cur_mlist = p;
        cur_style = DISPLAY_STYLE;
        mlist_penalties = false;
        mlist_to_hlist();
        p = link(TEMP_HEAD);
        adjust_tail = ADJUST_HEAD;
        b = hpack(p, NATURAL);
        p = list_ptr(b);
        t = adjust_tail;
        adjust_tail = null;
        w = width(b);
        z = display_width;
        s = display_indent;
        if (a == null || danger) {
            e = 0;
            q = 0;
        }
        else {
            e = width(a);
            q = e + math_quad(TEXT_SIZE);
        }
        if (w + q > z) {
            // ~~~ Squeeze the equation as much as possible; if there is an equation number that should go on a separate line by itself, set |e = 0|, 1201 ~~~
            if (e != 0 && (w - total_shrink[NORMAL] + q <= z
                || total_shrink[FIL] != 0
                || total_shrink[FILL] != 0
                || total_shrink[FILLL] != 0))
            {
                free_node(b, BOX_NODE_SIZE);
                b = hpack(p, z - q, EXACTLY);
            }
            else {
                e = 0;
                if (w > z) {
                    free_node(b, BOX_NODE_SIZE);
                    b = hpack(p, z, EXACTLY);
                }
            }
            w = width(b);
            // ~~~ End section 1201 ~~~
        }
        
        // ~~~ Determine the displacement, |d|, of the left edge of the equation, with respect to the line size |z|, assuming that |l = false|, 1202 ~~~
        d = half(z - w);
        if (e > 0 && d < 2*e) {
            // too close
            d = half(z - w - e);
            if (p != null
                && !is_char_node(p)
                && type(p) == GLUE_NODE)
            {
                d = 0;
            }
        }
        // ~~~ End section 1202 ~~~
        
        // ~~~ Append the glue or equation number preceding the display, 1203 ~~~
        tail_append(new_penalty(pre_display_penalty));
        if (d + s <= pre_display_size || l) {
             // not enough clearance
            g1 = ABOVE_DISPLAY_SKIP_CODE;
            g2 = BELOW_DISPLAY_SKIP_CODE;
        }
        else {
            g1 = ABOVE_DISPLAY_SHORT_SKIP_CODE;
            g2 = BELOW_DISPLAY_SHORT_SKIP_CODE;
        }
        if (l && e == 0) {
            // it follows that |type(a) = HLIST_NODE|
            shift_amount(a) = s;
            append_to_vlist(a);
            tail_append(new_penalty(INF_PENALTY));
        }
        else {
            tail_append(new_param_glue(g1));
        }
        // ~~~ End section 1203 ~~~
        // ~~~ Append the display and perhaps also the equation number, 1204 ~~~
        if (e != 0) {
            r = new_kern(z - w - e - d);
            if (l) {
                link(a) = r;
                link(r) = b;
                b = a;
                d = 0;
            }
            else {
                link(b) = r;
                link(r) = a;
            }
            b = hpack(b, NATURAL);
        }
        shift_amount(b) = s + d;
        append_to_vlist(b);
        // ~~~ End section 1204 ~~~
        // ~~~ Append the glue or equation number following the display, 1205 ~~~
        if (a != null
            && e == 0
            && !l)
        {
            tail_append(new_penalty(INF_PENALTY));
            shift_amount(a) = s + z - width(a);
            append_to_vlist(a);
            g2 = 0;
        }
        if (t != ADJUST_HEAD) {
            // migrating material comes after equation number
            link(tail) = link(ADJUST_HEAD);
            tail = t;
        }
        tail_append(new_penalty(post_display_penalty));
        if (g2 > 0) {
            tail_append(new_param_glue(g2));
        }
        // ~~~ End section 1205 ~~~
        resume_after_display();
        // ~~~ End section 1199 ~~~
    }
}
// ~~~ End section 1194 ~~~

// ~~~ Section 1200 ~~~
void resume_after_display() {
    if (cur_group != MATH_SHIFT_GROUP) {
        confusion("display");
    }
    unsave();
    prev_graf += 3;
    push_nest();
    mode = HMODE;
    space_factor = 1000;
    set_cur_lang;
    clang = cur_lang;
    prev_graf = (norm_min(left_hyphen_min)*64 + norm_min(right_hyphen_min))*0x10000 + cur_lang;
    // ~~~ Scan an optional space, 443 ~~~
    get_x_token();
    if (cur_cmd != SPACER) {
        back_input();
    }
    // ~~~ End section 443 ~~~
    if (nest_ptr == 1) {
        build_page();
    }
}
// ~~~ End section 1200 ~~~
