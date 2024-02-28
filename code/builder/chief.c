// ~~~ Section 1030 ~~~
// ~~~ Start file |chief.c|, 1382 ~~~
#include "builder.h"
#include "texerror.h"
#include "extensions.h"
#include "parser.h"
#include "font_metric.h"
#include "arithmetic.h"
#include "alignment.h"
#include "texmath.h"
// ~~~ End section 1382 ~~~

// ~~~ Declare action procedures for use by |main_control|, 1043 ~~~
// handle spaces when |space_factor != 1000|
void app_space() {
    pointer q; // glue node
    if (space_factor >= 2000 && xspace_skip != ZERO_GLUE) {
        q = new_param_glue(XSPACE_SKIP_CODE);
    }
    else {
        if (space_skip != ZERO_GLUE) {
            main_p = space_skip;
        }
        else {
            // ~~~ Find the glue specification, |main_p|, for text spaces in the current font, 1042 ~~~
            main_p = font_glue[cur_font];
            if (main_p == null) {
                main_p = new_spec(ZERO_GLUE);
                main_k = param_base[cur_font] + SPACE_CODE;
                width(main_p) = font_info[main_k].sc;       // that's |space(cur_font)|
                stretch(main_p) = font_info[main_k + 1].sc; // and |space_stretch(cur_font)|
                shrink(main_p) = font_info[main_k + 2].sc;  // and |space_shrink(cur_font)|
                font_glue[cur_font] = main_p;
            }
            // ~~~ End section 1042 ~~~
        }
        main_p = new_spec(main_p);
        // ~~~ Modify the glue specification in |main_p| according to the space factor, 1044 ~~~
        if (space_factor >= 2000) {
            width(main_p) += extra_space(cur_font);
        }
        stretch(main_p) = xn_over_d(stretch(main_p), space_factor, 1000);
        shrink(main_p) = xn_over_d(shrink(main_p), 1000, space_factor);
        // ~~~ End section 1044 ~~~
        q = new_glue(main_p);
        glue_ref_count(main_p) = null;
    }
    link(tail) = q;
    tail = q;
}

// ~~~ Section 1047 ~~~
void insert_dollar_sign() {
    back_input();
    cur_tok = MATH_SHIFT_TOKEN + '$';
    print_err("Missing $ inserted");
    help2("I've inserted a begin-math/end-math symbol since I think")
        ("you left one out. Proceed, with fingers crossed.");
    ins_error();
}
// ~~~ End section 1047 ~~~

// ~~~ Section 1050 ~~~
void report_illegal_case() {
    you_cant();
    help4("Sorry, but I'm not programmed to handle this case;")
        ("I'll just pretend that you didn't ask for it.")
        ("If you're in the wrong mode, you might be able to")
        ("return to the right one by typing `I}' or `I$' or `I\\par'.");
    error();
}
// ~~~ End section 1050 ~~~

// ~~~ Section 1051 ~~~
bool privileged() {
    if (mode > 0) {
        return true;
    }
    else {
        report_illegal_case();
        return false;
    }
}
// ~~~ End section 1051 ~~~

// ~~~ Section 1054 ~~~
// do this when \end or \dump occurs
bool its_all_over() {
    if (privileged()) {
        if (PAGE_HEAD == page_tail && head == tail && dead_cycles == 0) {
            return true;
        }
        back_input(); // we will try to end again after ejecting residual material
        tail_append(new_null_box());
        width(tail) = hsize;
        tail_append(new_glue(FILL_GLUE));
        tail_append(new_penalty(-0x40000000));
        build_page(); // append \hbox to \hsize{}\vfill\penalty-'10000000000
    }
    return false;
}
// ~~~ End section 1054 ~~~

// ~~~ Section 1069 ~~~
void extra_right_brace() {
    print_err("Extra }, or forgotten ");
    switch (cur_group) {
    case SEMI_SIMPLE_GROUP:
        print_esc("endgroup");
        break;
    
    case MATH_SHIFT_GROUP:
        print_char('$');
        break;

    case MATH_LEFT_GROUP:
        print_esc("right");
    }
    help5("I've deleted a group-closing symbol because it seems to be")
        ("spurious, as in `$x}$'. But perhaps the } is legitimate and")
        ("you forgot something else, as in `\\hbox{$x}'. In such cases")
        ("the way to recover is to insert both the forgotten and the")
        ("deleted material, e.g., by typing `I$}'.");
    error();
    incr(align_state);
}
// ~~~ End section 1069 ~~~

// ~~~ Section 1129 ~~~
void no_align_error() {
    print_err("Misplaced ");
    print_esc("noalign");
    help2("I expect to see \\noalign only after the \\cr of")
        ("an alignment. Proceed, and I'll ignore this case.");
    error();
}

void omit_error() {
    print_err("Misplaced ");
    print_esc("omit");
    help2("I expect to see \\omit only after tab marks or the \\cr of")
        ("an alignment. Proceed, and I'll ignore this case.");
    error();
}
// ~~~ End section 1129 ~~~

// ~~~ Section 1135 ~~~
void cs_error() {
    print_err("Extra ");
    print_esc("endcsname");
    help1("I'm ignoring this, since I wasn't doing a \\csname.");
    error();
}
// ~~~ End section 1135 ~~~

// ~~~ Section 1376 ~~~
void fix_language() {
    ASCII_code l; // the new current language
    if (language <= 0) {
        l = 0;
    }
    else if (language > 255) {
        l = 0;
    }
    else {
        l = language;
    }
    if (l != clang) {
        new_whatsit(LANGUAGE_NODE, SMALL_NODE_SIZE);
        what_lang(tail) = l;
        clang = l;
        what_lhm(tail) = norm_min(left_hyphen_min);
        what_rhm(tail) = norm_min(right_hyphen_min);
    }
}
// ~~~ End section 1376 ~~~
// ~~~ End section 1043 ~~~

// governs TeX's activities
void main_control() {
    int t; // general-purpose temporary variable
    if (every_job != null) {
        begin_token_list(every_job, EVERY_JOB_TEXT);
    }

big_switch:
    get_x_token();

reswitch:
    // ~~~ Give diagnostic information, if requested, 1031 ~~~
    if (interrupt != 0 && ok_to_interrupt) {
        back_input();
        check_interrupt;
        goto big_switch;
    }
#ifdef DEBUG
    if (panicking) {
        check_mem(false);
    }
#endif
    if (tracing_commands > 0) {
        show_cur_cmd_chr();
    }
    // ~~~ End section 1031 ~~~
    switch (abs(mode) + cur_cmd) {
    case HMODE + LETTER:
    case HMODE + OTHER_CHAR:
    case HMODE + CHAR_GIVEN:
        goto main_loop;
    
    case HMODE + CHAR_NUM:
        scan_char_num();
        cur_chr = cur_val;
        goto main_loop;
    
    case HMODE + NO_BOUNDARY:
        get_x_token();
        if (cur_cmd == LETTER
            || cur_cmd == OTHER_CHAR
            || cur_cmd == CHAR_GIVEN
            || cur_cmd == CHAR_NUM)
        {
            cancel_boundary = true;
        }
        goto reswitch;

    case HMODE + SPACER:
        if (space_factor == 1000) {
            goto append_normal_space;
        }
        else {
            app_space();
        }
        break;
    
    case HMODE + EX_SPACE:
    case MMODE + EX_SPACE:
        goto append_normal_space;
    
    // ~~~ Cases of |main_control| that are not part of the inner loop, 1045 ~~~
    any_mode(RELAX):
    case VMODE + SPACER:
    case MMODE + SPACER:
    case MMODE + NO_BOUNDARY:
        do_nothing;
        break;
    
    any_mode(IGNORE_SPACES):
        // ~~~ Get the next non-blank non-call token, 406 ~~~
        do {
            get_x_token();
        } while (cur_cmd == SPACER);
        // ~~~ End section 406 ~~~
        goto reswitch;
    
    case VMODE + STOP:
        if (its_all_over()) {
            // this is the only way out
            return;
        }
        break;
    
    // ~~~ Forbidden cases detected in |main_control|, 1048 ~~~
    case VMODE + VMOVE:
    case HMODE + HMOVE:
    case MMODE + HMOVE:
    any_mode(LAST_ITEM):
    
    // ~~~ Section 1098 ~~~
    case VMODE + VADJUST:
    // ~~~ End section 1098 ~~~
    
    // ~~~ Section 1111 ~~~
    case VMODE + ITAL_CORR:
    // ~~~ End section 1111 ~~~
    
    // ~~~ Section 1144 ~~~
    non_math(EQ_NO):
    // ~~~ End section 1144 ~~~
    // ~~~ End section 1048 ~~~
    any_mode(MAC_PARAM):
        report_illegal_case();
        break;
    
    // ~~~ Math-only cases in non-math modes, or vice versa, 1046 ~~~
    non_math(SUP_MARK):
    non_math(SUB_MARK):
    non_math(MATH_CHAR_NUM):
    non_math(MATH_GIVEN):
    non_math(MATH_COMP):
    non_math(DELIM_NUM):
    non_math(LEFT_RIGHT):
    non_math(ABOVE):
    non_math(RADICAL):
    non_math(MATH_STYLE):
    non_math(MATH_CHOICE):
    non_math(VCENTER):
    non_math(NON_SCRIPT):
    non_math(MKERN):
    non_math(LIMIT_SWITCH):
    non_math(MSKIP):
    non_math(MATH_ACCENT):
    case MMODE + ENDV:
    case MMODE + PAR_END:
    case MMODE + STOP:
    case MMODE + VSKIP:
    case MMODE + UN_VBOX:
    case MMODE + VALIGN:
    case MMODE + HRULE:
    // ~~~ End section 1046 ~~~
        insert_dollar_sign();
        break;
    
    // ~~~ Cases of |main_control| that build boxes and lists, 1056 ~~~
    case VMODE + HRULE:
    case HMODE + VRULE:
    case MMODE + VRULE:
        tail_append(scan_rule_spec());
        if (abs(mode) == VMODE) {
            prev_depth = IGNORE_DEPTH;
        }
        else if (abs(mode) == HMODE) {
            space_factor = 1000;
        }
        break;
    
    // ~~~ Section 1057 ~~~
    case VMODE + VSKIP:
    case HMODE + HSKIP:
    case MMODE + HSKIP:
    case MMODE + MSKIP:
        append_glue();
        break;
    
    any_mode(KERN):
    case MMODE + MKERN:
        append_kern();
        break;
    // ~~~ End section 1057 ~~~
    
    // ~~~ Section 1063 ~~~
    non_math(LEFT_BRACE):
        new_save_level(SIMPLE_GROUP);
        break;
    
    any_mode(BEGIN_GROUP):
        new_save_level(SEMI_SIMPLE_GROUP);
        break;
    
    any_mode(END_GROUP):
        if (cur_group == SEMI_SIMPLE_GROUP) {
            unsave();
        }
        else {
            off_save();
        }
        break;
    // ~~~ End section 1063 ~~~
    
    // ~~~ Section 1067 ~~~
    any_mode(RIGHT_BRACE):
        handle_right_brace();
        break;
    // ~~~ End section 1067 ~~~
    
    // ~~~ Section 1073 ~~~
    case VMODE + HMOVE:
    case HMODE + VMOVE:
    case MMODE + VMOVE:
        t = cur_chr;
        scan_normal_dimen;
        if (t == 0) {
            scan_box(cur_val);
        }
        else {
            scan_box(-cur_val);
        }
        break;
    
    any_mode(LEADER_SHIP):
        scan_box(LEADER_FLAG - A_LEADERS + cur_chr);
        break;
    
    any_mode(MAKE_BOX):
        begin_box(0);
        break;
    // ~~~ End section 1073 ~~~
    
    // ~~~ Section 1090 ~~~
    case VMODE + START_PAR:
        new_graf(cur_chr > 0);
        break;
    
    case VMODE + LETTER:
    case VMODE + OTHER_CHAR:
    case VMODE + CHAR_NUM:
    case VMODE + CHAR_GIVEN:
    case VMODE + MATH_SHIFT:
    case VMODE + UN_HBOX:
    case VMODE + VRULE:
    case VMODE + ACCENT:
    case VMODE + DISCRETIONARY:
    case VMODE + HSKIP:
    case VMODE + VALIGN:
    case VMODE + EX_SPACE:
    case VMODE + NO_BOUNDARY:
        back_input();
        new_graf(true);
        break;
    // ~~~ End section 1090 ~~~
    
    // ~~~ Section 1092 ~~~
    case HMODE + START_PAR:
    case MMODE + START_PAR:
        indent_in_hmode();
        break;
    // ~~~ End section 1092 ~~~
    
    // ~~~ Section 1094 ~~~
    case VMODE + PAR_END:
        normal_paragraph();
        if (mode > 0) {
            build_page();
        }
        break;
    
    case HMODE + PAR_END:
        if (align_state < 0) {
            off_save(); // this tries to recover from an alignment that didn't end properly
        }
        end_graf(); // this takes us to the enclosing mode, if |mode > 0|
        if (mode == VMODE) {
            build_page();
        }
        break;
    
    case HMODE + STOP:
    case HMODE + VSKIP:
    case HMODE + HRULE:
    case HMODE + UN_VBOX:
    case HMODE + HALIGN:
        head_for_vmode();
        break;
    // ~~~ End section 1094 ~~~
    
    // ~~~ Section 1097 ~~~
    any_mode(INSERT):
    case HMODE + VADJUST:
    case MMODE + VADJUST:
        begin_insert_or_adjust();
        break;
    
    any_mode(MARK):
        make_mark();
        break;
    // ~~~ End section 1097 ~~~
    
    // ~~~ Section 1102 ~~~
    any_mode(BREAK_PENALTY):
        append_penalty();
        break;
    // ~~~ End section 1102 ~~~
    
    // ~~~ Section 1104 ~~~
    any_mode(REMOVE_ITEM):
        delete_last();
        break;
    // ~~~ End section 1104 ~~~
    
    // ~~~ Section 1109 ~~~
    case VMODE + UN_VBOX:
    case HMODE + UN_HBOX:
    case MMODE + UN_HBOX:
        unpackage();
        break;
    // ~~~ End section 1109 ~~~
    
    // ~~~ Section 1112 ~~~
    case HMODE + ITAL_CORR:
        append_italic_correction();
        break;
    
    case MMODE + ITAL_CORR:
        tail_append(new_kern(0));
        break;
    // ~~~ End section 1112 ~~~
    
    // ~~~ Section 1116 ~~~
    case HMODE + DISCRETIONARY:
    case MMODE + DISCRETIONARY:
        append_discretionary();
        break;
    // ~~~ End section 1116 ~~~
    
    // ~~~ Section 1122 ~~~
    case HMODE + ACCENT:
        make_accent();
        break;
    // ~~~ End section 1122 ~~~
    
    // ~~~ Section 1126 ~~~
    any_mode(CAR_RET):
    any_mode(TAB_MARK):
        align_error();
        break;
    
    any_mode(NO_ALIGN):
        no_align_error();
        break;
    
    any_mode(OMIT):
        omit_error();
        break;
    // ~~~ End section 1126 ~~~
    
    // ~~~ Section 1130 ~~~
    case VMODE + HALIGN:
    case HMODE + VALIGN:
        init_align();
        break;
    
    case MMODE + HALIGN:
        if (privileged()) {
            if (cur_group == MATH_SHIFT_GROUP) {
                init_align();
            }
            else {
                off_save();
            }
        }
        break;
    
    case VMODE + ENDV:
    case HMODE + ENDV:
        do_endv();
        break;
    // ~~~ End section 1130 ~~~
    
    // ~~~ Section 1134 ~~~
    any_mode(END_CS_NAME):
        cs_error();
        break;
    // ~~~ End section 1134 ~~~
    
    // ~~~ Section 1137 ~~~
    case HMODE + MATH_SHIFT:
        init_math();
        break;
    // ~~~ End section 1137 ~~~
    
    // ~~~ Section 1140 ~~~
    case MMODE + EQ_NO:
        if (privileged()) {
            if (cur_group == MATH_SHIFT_GROUP) {
                start_eq_no();
            }
            else {
                off_save();
            }
        }
        break;
    // ~~~ End section 1140 ~~~
    
    // ~~~ Section 1150 ~~~
    case MMODE + LEFT_BRACE:
        tail_append(new_noad());
        back_input();
        scan_math(nucleus(tail));
        break;
    // ~~~ End section 1150 ~~~
    
    // ~~~ Section 1154 ~~~
    case MMODE + LETTER:
    case MMODE + OTHER_CHAR:
    case MMODE + CHAR_GIVEN:
        set_math_char(ho(math_code(cur_chr)));
        break;
    
    case MMODE + CHAR_NUM:
        scan_char_num();
        cur_chr = cur_val;
        set_math_char(ho(math_code(cur_chr)));
        break;
    
    case MMODE + MATH_CHAR_NUM:
        scan_fifteen_bit_int();
        set_math_char(cur_val);
        break;
    
    case MMODE + MATH_GIVEN:
        set_math_char(cur_chr);
        break;
    
    case MMODE + DELIM_NUM:
        scan_twenty_seven_bit_int();
        set_math_char(cur_val / 0x1000);
        break;
    // ~~~ End section 1154 ~~~
    
    // ~~~ Section 1158 ~~~
    case MMODE + MATH_COMP:
        tail_append(new_noad());
        type(tail) = cur_chr;
        scan_math(nucleus(tail));
        break;
    
    case MMODE + LIMIT_SWITCH:
        math_limit_switch();
        break;
    // ~~~ End section 1158 ~~~
    
    // ~~~ Section 1162 ~~~
    case MMODE + RADICAL:
        math_radical();
        break;
    // ~~~ End section 1162 ~~~
    
    // ~~~ Section 1164 ~~~
    case MMODE + ACCENT:
    case MMODE + MATH_ACCENT:
        math_ac();
        break;
    // ~~~ End section 1164 ~~~
    
    // ~~~ Section 1167 ~~~
    case MMODE + VCENTER:
        scan_spec(VCENTER_GROUP, false);
        normal_paragraph();
        push_nest();
        mode = -VMODE;
        prev_depth = IGNORE_DEPTH;
        if (every_vbox != null) {
            begin_token_list(every_vbox, EVERY_VBOX_TEXT);
        }
        break;
    // ~~~ End section 1167 ~~~
    
    // ~~~ Section 1171 ~~~
    case MMODE + MATH_STYLE:
        tail_append(new_style(cur_chr));
        break;
    
    case MMODE + NON_SCRIPT:
        tail_append(new_glue(ZERO_GLUE));
        subtype(tail) = COND_MATH_GLUE;
        break;
    
    case MMODE + MATH_CHOICE:
        append_choices();
        break;
    // ~~~ End section 1171 ~~~
    
    // ~~~ Section 1175 ~~~
    case MMODE + SUB_MARK:
    case MMODE + SUP_MARK:
        sub_sup();
        break;
    // ~~~ End section 1175 ~~~
    
    // ~~~ Section 1180 ~~~
    case MMODE + ABOVE:
        math_fraction();
        break;
    // ~~~ End section 1180 ~~~
    
    // ~~~ Section 1190 ~~~
    case MMODE + LEFT_RIGHT:
        math_left_right();
        break;
    // ~~~ End section 1190 ~~~
    
    // ~~~ Section 1193 ~~~
    case MMODE + MATH_SHIFT:
        if (cur_group == MATH_SHIFT_GROUP) {
            after_math();
        }
        else {
            off_save();
        }
        break;
    // ~~~ End section 1193 ~~~
    // ~~~ End section 1056 ~~~
    
    // ~~~ Cases of |main_control| that don't depend on |mode|, 1210 ~~~
    any_mode(TOKS_REGISTER):
    any_mode(ASSIGN_TOKS):
    any_mode(ASSIGN_INT):
    any_mode(ASSIGN_DIMEN):
    any_mode(ASSIGN_GLUE):
    any_mode(ASSIGN_MU_GLUE):
    any_mode(ASSIGN_FONT_DIMEN):
    any_mode(ASSIGN_FONT_INT):
    any_mode(SET_AUX):
    any_mode(SET_PREV_GRAF):
    any_mode(SET_PAGE_DIMEN):
    any_mode(SET_PAGE_INT):
    any_mode(SET_BOX_DIMEN):
    any_mode(SET_SHAPE):
    any_mode(DEF_CODE):
    any_mode(DEF_FAMILY):
    any_mode(SET_FONT):
    any_mode(DEF_FONT):
    any_mode(REGISTER):
    any_mode(ADVANCE):
    any_mode(MULTIPLY):
    any_mode(DIVIDE):
    any_mode(PREFIX):
    any_mode(LET):
    any_mode(SHORTHAND_DEF):
    any_mode(READ_TO_CS):
    any_mode(DEF):
    any_mode(SET_BOX):
    any_mode(HYPH_DATA):
    any_mode(SET_INTERACTION):
        prefixed_command();
        break;
    
    // ~~~ Section 1268 ~~~
    any_mode(AFTER_ASSIGNMENT):
        get_token();
        after_token = cur_tok;
        break;
    // ~~~ End section 1268 ~~~
    
    // ~~~ Section 1271 ~~~
    any_mode(AFTER_GROUP):
        get_token();
        save_for_after(cur_tok);
        break;
    // ~~~ End section 1271 ~~~
    
    // ~~~ Section 1274 ~~~
    any_mode(IN_STREAM):
        open_or_close_in();
        break;
    // ~~~ End section 1274 ~~~
    
    // ~~~ Section 1276 ~~~
    any_mode(MESSAGE):
        issue_message();
        break;
    // ~~~ End section 1276 ~~~
    
    // ~~~ Section 1285 ~~~
    any_mode(CASE_SHIFT):
        shift_case();
        break;
    // ~~~ End section 1285 ~~~
    
    // ~~~ Section 1290 ~~~
    any_mode(XRAY):
        show_whatever();
        break;
    // ~~~ End section 1290 ~~~
    // ~~~ End section 1210 ~~~
    
    // ~~~ Cases of |main_control| that are for extensions to TeX, 1347 ~~~
    any_mode(EXTENSION):
        do_extension();
        break;
    // ~~~ End section 1347 ~~~
    // ~~~ End section 1045 ~~~

    } // end of the big |case| statement
    goto big_switch;

main_loop:
    // ~~~ Append character |cur_chr| and the following characters (if any) to the current hlist in the current font; |goto reswitch| when a non-character has been fetched, 1034 ~~~
    adjust_space_factor;
    main_f = cur_font;
    bchar = font_bchar[main_f];
    false_bchar = font_false_bchar[main_f];
    if (mode > 0 && language != clang) {
        fix_language();
    }
    fast_get_avail(lig_stack);
    font(lig_stack) = main_f;
    cur_l = cur_chr;
    character(lig_stack) = cur_l;
    cur_q = tail;
    if (cancel_boundary) {
        cancel_boundary = false;
        main_k = NON_ADDRESS;
    }
    else {
        main_k = bchar_label[main_f];
    }
    if (main_k == NON_ADDRESS) {
        goto main_loop_move_2; // no left boundary processing
    }
    cur_r = cur_l;
    cur_l = NON_CHAR;
    goto main_lig_loop_1; // begin with cursor after left boundary
    
main_loop_wrapup:
    // ~~~ Make a ligature node, if |ligature_present|; insert a null discretionary, if appropriate, 1035 ~~~
    wrapup(rt_hit);
    // ~~~ End section 1035 ~~~
    
main_loop_move:
    // ~~~ If the cursor is immediately followed by the right boundary, |goto reswitch|; if it's followed by an invalid character, |goto big_switch|; otherwise move the cursor one step to the right and |goto main_lig_loop|, 1036 ~~~
    if (lig_stack == null) {
        goto reswitch;
    }
    cur_q = tail;
    cur_l = character(lig_stack);
    
main_loop_move_1:
    if (!is_char_node(lig_stack)) {
        goto main_loop_move_lig;
    }
    
main_loop_move_2:
    if (cur_chr < font_bc[main_f] || cur_chr > font_ec[main_f]) {
        char_warning(main_f, cur_chr);
        free_avail(lig_stack);
        goto big_switch;
    }
    main_i = char_info(main_f, cur_l);
    if (!char_exists(main_i)) {
        char_warning(main_f, cur_chr);
        free_avail(lig_stack);
        goto big_switch;
    }
    link(tail) = lig_stack;
    tail = lig_stack; // |main_loop_lookahead| is next
    // ~~~ End section 1036 ~~~
    
main_loop_lookahead:
    // ~~~ Look ahead for another character, or leave |lig_stack| empty if there's none there, 1038 ~~~
    get_next(); // set only |cur_cmd| and |cur_chr|, for speed
    if (cur_cmd == LETTER
        || cur_cmd == OTHER_CHAR
        || cur_cmd == CHAR_GIVEN)
    {
        goto main_loop_lookahead_1;
    }
    x_token(); // now expand and set |cur_cmd|, |cur_chr|, |cur_tok|
    if (cur_cmd == LETTER
        || cur_cmd == OTHER_CHAR
        || cur_cmd == CHAR_GIVEN)
    {
        goto main_loop_lookahead_1;
    }
    if (cur_cmd == CHAR_NUM) {
        scan_char_num();
        cur_chr = cur_val;
        goto main_loop_lookahead_1;
    }
    if (cur_cmd == NO_BOUNDARY) {
        bchar = NON_CHAR;
    }
    cur_r = bchar;
    lig_stack = null;
    goto main_lig_loop;
    
main_loop_lookahead_1:
    adjust_space_factor;
    fast_get_avail(lig_stack);
    font(lig_stack) = main_f;
    cur_r = cur_chr;
    character(lig_stack) = cur_r;
    if (cur_r == false_bchar) {
        cur_r = NON_CHAR; // this prevents spurious ligatures
    }
    // ~~~ End section 1038 ~~~
    
main_lig_loop:
    // ~~~ If there's a ligature/kern command relevant to |cur_l| and |cur_r|, adjust the text appropriately; exit to |main_loop_wrapup|, 1039 ~~~
    if (char_tag(main_i) != LIG_TAG ||cur_r == NON_CHAR) {
        goto main_loop_wrapup;
    }
    main_k = lig_kern_start(main_f, main_i);
    main_j = font_info[main_k];
    if (skip_byte(main_j) <= STOP_FLAG) {
        goto main_lig_loop_2;
    }
    main_k = lig_kern_restart(main_f, main_j);
    
main_lig_loop_1:
    main_j = font_info[main_k];
    
main_lig_loop_2:
    if (next_char(main_j) == cur_r && skip_byte(main_j) <= STOP_FLAG) {
        // ~~~ Do ligature or kern command, returning to |main_lig_loop| or |main_loop_wrapup| or |main_loop_move|, 1040 ~~~
        if (op_byte(main_j) >= KERN_FLAG) {
            wrapup(rt_hit);
            tail_append(new_kern(char_kern(main_f, main_j)));
            goto main_loop_move;
        }
        if (cur_l == NON_CHAR) {
            lft_hit = true;
        }
        else if (lig_stack == null) {
            rt_hit = true;
        }
        check_interrupt; // allow a way out in case there's an infinite ligature loop
        switch (op_byte(main_j)) {
        case 1:
        case 5:
            // =:|, =:|>
            cur_l = rem_byte(main_j);
            main_i = char_info(main_f, cur_l);
            ligature_present = true;
            break;
        
        case 2:
        case 6:
            // |=:, |=:>
            cur_r = rem_byte(main_j);
            if (lig_stack == null) {
                // right boundary character is being consumed
                lig_stack = new_lig_item(cur_r);
                bchar = NON_CHAR;
            }
            else if (is_char_node(lig_stack)) {
                // |link(lig_stack) = null|
                main_p = lig_stack;
                lig_stack = new_lig_item(cur_r);
                lig_ptr(lig_stack) = main_p;
            }
            else {
                character(lig_stack) = cur_r;
            }
            break;
        
        case 3:
            // |=:|
            cur_r = rem_byte(main_j);
            main_p = lig_stack;
            lig_stack = new_lig_item(cur_r);
            link(lig_stack) = main_p;
            break;
        
        case 7:
        case 11:
            // |=:|>, |=:|>>
            wrapup(false);
            cur_q = tail;
            cur_l = rem_byte(main_j);
            main_i = char_info(main_f, cur_l);
            ligature_present = true;
            break;
        
        default:
            // =:
            cur_l = rem_byte(main_j);
            ligature_present = true;
            if (lig_stack == null) {
                goto main_loop_wrapup;
            }
            else {
                goto main_loop_move_1;
            }
        }
        if (op_byte(main_j) > 4 && op_byte(main_j) != 7) {
            goto main_loop_wrapup;
        }
        if (cur_l < NON_CHAR) {
            goto main_lig_loop;
        }
        main_k = bchar_label[main_f];
        goto main_lig_loop_1;
        // ~~~ End section 1040 ~~~
    }
    if (skip_byte(main_j) == 0) {
        incr(main_k);
    }
    else {
        if (skip_byte(main_j) >= STOP_FLAG) {
            goto main_loop_wrapup;
        }
        main_k += skip_byte(main_j) + 1;
    }
    goto main_lig_loop_1;
    // ~~~ End section 1039 ~~~
    
main_loop_move_lig:
    // ~~~ Move the cursor past a pseudo-ligature, then |goto main_loop_lookahead| or |main_lig_loop|, 1037 ~~~
    main_p = lig_ptr(lig_stack);
    if (main_p > null) {
        tail_append(main_p); // append a single character
    }
    temp_ptr = lig_stack;
    lig_stack = link(temp_ptr);
    free_node(temp_ptr, SMALL_NODE_SIZE);
    main_i = char_info(main_f, cur_l);
    ligature_present = true;
    if (lig_stack == null) {
        if (main_p > null) {
            goto main_loop_lookahead;
        }
        else {
            cur_r = bchar;
        }
    }
    else {
        cur_r = character(lig_stack);
    }
    goto main_lig_loop;
    // ~~~ End section 1037 ~~~
    // ~~~ End section 1034 ~~~

append_normal_space:
    // ~~~ Append a normal inter-word space to the current list, then |goto big_switch|, 1041 ~~~
    if (space_skip == ZERO_GLUE) {
        // ~~~ Find the glue specification, |main_p|, for text spaces in the current font, 1042 ~~~
        main_p = font_glue[cur_font];
        if (main_p == null) {
            main_p = new_spec(ZERO_GLUE);
            main_k = param_base[cur_font] + SPACE_CODE;
            width(main_p) = font_info[main_k].sc;       // that's |space(cur_font)|
            stretch(main_p) = font_info[main_k + 1].sc; // and |space_stretch(cur_font)|
            shrink(main_p) = font_info[main_k + 2].sc;  // and |space_shrink(cur_font)|
            font_glue[cur_font] = main_p;
        }
        // ~~~ End section 1042 ~~~
        temp_ptr = new_glue(main_p);
    }
    else {
        temp_ptr = new_param_glue(SPACE_SKIP_CODE);
    }
    link(tail) = temp_ptr;
    tail = temp_ptr;
    goto big_switch;
    // ~~~ End section 1041 ~~~
}
// ~~~ End section 1030 ~~~

// ~~~ Section 1049 ~~~
void you_cant() {
    print_err("You can't use `");
    print_cmd_chr(cur_cmd, cur_chr);
    print("' in ");
    print_mode(mode);
}
// ~~~ End section 1049 ~~~
