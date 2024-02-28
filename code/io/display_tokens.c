// ~~~ Section 292 ~~~
// ~~~ Start file |display_tokens.c|, 1382 ~~~
#include "datastructures.h"
#include "io.h"
// ~~~ End section 1382 ~~~

void show_token_list(int p, int q, int l) {
    int m, c;             // pieces of a token
    ASCII_code match_chr; // character used in a '|MATCH|'
    ASCII_code n;         // the highest parameter number, as an ASCII digit}
    match_chr = '#';
    n = '0';
    tally = 0;
    while (p != null && tally < l) {
        if (p == q) {
            // ~~~ Do magic computation, 320 ~~~
            set_trick_count;
            // ~~~ End section 320 ~~~
        }
        // ~~~ Display token |p|, and |return| if there are problems, 293 ~~~
        if ( p < hi_mem_min || p > mem_end) {
            print_esc("CLOBBERED.");
            return;
        }
        if (info(p) >= CS_TOKEN_FLAG) {
            print_cs(info(p) - CS_TOKEN_FLAG);
        }
        else {
            m = info(p) / 256;
            c = info(p) % 256;
            if (info(p) < 0) {
                print_esc("BAD.");
            }
            else {
                // ~~~ Display the token (|m|, |c|), 294 ~~~
                switch(m) {
                case LEFT_BRACE:
                case RIGHT_BRACE:
                case MATH_SHIFT:
                case TAB_MARK:
                case SUP_MARK:
                case SUB_MARK:
                case SPACER:
                case LETTER:
                case OTHER_CHAR:
                    print_strnumber(c);
                    break;
                
                case MAC_PARAM:
                    print_strnumber(c);
                    print_strnumber(c);
                    break;
                
                case OUT_PARAM:
                    print_strnumber(match_chr);
                    if (c <= 9) {
                        print_char(c + '0');
                    }
                    else {
                        print_char('!');
                        return;
                    }
                    break;
                
                case MATCH:
                    match_chr = c;
                    print_strnumber(c);
                    incr(n);
                    print_char(n);
                    if (n > '9') {
                        return;
                    }
                    break;
                
                case END_MATCH:
                    print("->");
                    break;
                
                default:
                    print_esc("BAD.");
                }
                // ~~~ End section 294 ~~~
            }
        }
        // ~~~ End section 293 ~~~
        p = link(p);
    }
    if (p != null) {
        print_esc("ETC.");
    }
}
// ~~~ End section 292 ~~~

// ~~~ Section 295 ~~~
void token_show(pointer p) {
    if (p != null) {
        show_token_list(link(p), null, 10000000);
    }
}
// ~~~ End section 295 ~~~

// ~~~ Section 296 ~~~
void print_meaning() {
    print_cmd_chr(cur_cmd, cur_chr);
    if (cur_cmd >= CALL) {
        print_char(':');
        print_ln();
        token_show(cur_chr);
    }
    else if (cur_cmd == TOP_BOT_MARK) {
        print_char(':');
        print_ln();
        token_show(cur_mark[cur_chr]);
    }
}
// ~~~ End section 296 ~~~

// ~~~ Section 298 ~~~
void print_cmd_chr(quarterword cmd, halfword chr_code) {
    switch(cmd) {
    case LEFT_BRACE:
        chr_cmd("begin-group character ");
        break;
    
    case RIGHT_BRACE:
        chr_cmd("end-group character ");
        break;
    
    case MATH_SHIFT:
        chr_cmd("math shift character ");
        break;
    
    case MAC_PARAM:
        chr_cmd("macro parameter character ");
        break;
    
    case SUP_MARK:
        chr_cmd("superscript character ");
        break;
    
    case SUB_MARK:
        chr_cmd("subscript character ");
        break;
    
    case ENDV:
        print("end of alignment template");
        break;
    
    case SPACER:
        chr_cmd("blank space ");
        break;
    
    case LETTER:
        chr_cmd("the letter ");
        break;
    
    case OTHER_CHAR:
        chr_cmd("the character ");
        break;

    // ~~~ Cases of |print_cmd_chr| for symbolic printing of primitives, 227 ~~~
    case ASSIGN_GLUE:
    case ASSIGN_MU_GLUE:
        if (chr_code < SKIP_BASE) {
            print_skip_param(chr_code - GLUE_BASE);
        }
        else if (chr_code < MU_SKIP_BASE) {
            print_esc("skip");
            print_int(chr_code - SKIP_BASE);
        }
        else {
            print_esc("muskip");
            print_int(chr_code - MU_SKIP_BASE);
        }
        break;
    
    // ~~~ Section 231 ~~~
    case ASSIGN_TOKS:
        if (chr_code >= TOKS_BASE) {
            print_esc("toks");
            print_int(chr_code - TOKS_BASE);
        }
        else {
            switch(chr_code) {
            case OUTPUT_ROUTINE_LOC:
                print_esc("output");
                break;
            
            case EVERY_PAR_LOC:
                print_esc("everypar");
                break;
            
            case EVERY_MATH_LOC:
                print_esc("everymath");
                break;
            
            case EVERY_DISPLAY_LOC:
                print_esc("everydisplay");
                break;
            
            case EVERY_HBOX_LOC:
                print_esc("everyhbox");
                break;
            
            case EVERY_VBOX_LOC:
                print_esc("everyvbox");
                break;
            
            case EVERY_JOB_LOC:
                print_esc("everyjob");
                break;
            
            case EVERY_CR_LOC:
                print_esc("everycr");
                break;
            
            default:
                print_esc("errhelp");
            }
        }
        break;
    // ~~~ End section 231 ~~~
    
    // ~~~ Section 239 ~~~
    case ASSIGN_INT:
        if (chr_code < COUNT_BASE) {
            print_param(chr_code - INT_BASE);
        }
        else {
            print_esc("count");
            print_int(chr_code - COUNT_BASE);
        }
        break;
    // ~~~ End section 239 ~~~
    
    // ~~~ Section 249 ~~~
    case ASSIGN_DIMEN:
        if (chr_code < SCALED_BASE) {
            print_length_param(chr_code - DIMEN_BASE);
        }
        else {
            print_esc("dimen");
            print_int(chr_code - SCALED_BASE);
        }
        break;
    // ~~~ End section 249 ~~~
    
    // ~~~ Section 266 ~~~
    case ACCENT:
        print_esc("accent");
        break;
    
    case ADVANCE:
        print_esc("advance");
        break;
    
    case AFTER_ASSIGNMENT:
        print_esc("afterassignment");
        break;
    
    case AFTER_GROUP:
        print_esc("aftergroup");
        break;
    
    case ASSIGN_FONT_DIMEN:
        print_esc("fontdimen");
        break;
    
    case BEGIN_GROUP:
        print_esc("begingroup");
        break;
    
    case BREAK_PENALTY:
        print_esc("penalty");
        break;
    
    case CHAR_NUM:
        print_esc("char");
        break;
    
    case CS_NAME:
        print_esc("csname");
        break;
    
    case DEF_FONT:
        print_esc("font");
        break;
    
    case DELIM_NUM:
        print_esc("delimiter");
        break;
    
    case DIVIDE:
        print_esc("divide");
        break;
    
    case END_CS_NAME:
        print_esc("endcsname");
        break;
    
    case END_GROUP:
        print_esc("endgroup");
        break;
    
    case EX_SPACE:
        print_esc(" ");
        break;
    
    case EXPAND_AFTER:
        print_esc("expandafter");
        break;
    
    case HALIGN:
        print_esc("halign");
        break;
    
    case HRULE:
        print_esc("hrule");
        break;
    
    case IGNORE_SPACES:
        print_esc("ignorespaces");
        break;
    
    case INSERT:
        print_esc("insert");
        break;
    
    case ITAL_CORR:
        print_esc("/");
        break;
    
    case MARK:
        print_esc("mark");
        break;
    
    case MATH_ACCENT:
        print_esc("mathaccent");
        break;
    
    case MATH_CHAR_NUM:
        print_esc("mathchar");
        break;
    
    case MATH_CHOICE:
        print_esc("mathchoice");
        break;
    
    case MULTIPLY:
        print_esc("multiply");
        break;
    
    case NO_ALIGN:
        print_esc("noalign");
        break;
    
    case NO_BOUNDARY:
        print_esc("noboundary");
        break;
    
    case NO_EXPAND:
        print_esc("noexpand");
        break;
    
    case NON_SCRIPT:
        print_esc("nonscript");
        break;
    
    case OMIT:
        print_esc("omit");
        break;
    
    case RADICAL:
        print_esc("radical");
        break;
    
    case READ_TO_CS:
        print_esc("read");
        break;
    
    case RELAX:
        print_esc("relax");
        break;
    
    case SET_BOX:
        print_esc("setbox");
        break;
    
    case SET_PREV_GRAF:
        print_esc("prevgraf");
        break;
    
    case SET_SHAPE:
        print_esc("parshape");
        break;
    
    case THE:
        print_esc("the");
        break;
    
    case TOKS_REGISTER:
        print_esc("toks");
        break;
    
    case VADJUST:
        print_esc("vadjust");
        break;
    
    case VALIGN:
        print_esc("valign");
        break;
    
    case VCENTER:
        print_esc("vcenter");
        break;
    
    case VRULE:
        print_esc("vrule");
        break;
    // ~~~ End section 266 ~~~
    
    // ~~~ Section 335 ~~~
    case PAR_END:
        print_esc("par");
        break;
    // ~~~ End section 335 ~~~
    
    // ~~~ Section 377 ~~~
    case INPUT:
        if (chr_code == 0) {
            print_esc("input");
        }
        else {
            print_esc("endinput");
        }
        break;
    // ~~~ End section 377 ~~~
    
    // ~~~ Section 385 ~~~
    case TOP_BOT_MARK:
        switch (chr_code) {
        case FIRST_MARK_CODE:
            print_esc("firstmark");
            break;
        
        case BOT_MARK_CODE:
            print_esc("botmark");
            break;
        
        case SPLIT_FIRST_MARK_CODE:
            print_esc("splitfirstmark");
            break;
        
        case SPLIT_BOT_MARK_CODE:
            print_esc("splitbotmark");
            break;
        
        default:
            print_esc("topmark");
        } 
        break;
    // ~~~ End section 385 ~~~
    
    // ~~~ Section 412 ~~~
    case REGISTER:
        if (chr_code == INT_VAL) {
            print_esc("count");
        }
        else if (chr_code == DIMEN_VAL) {
            print_esc("dimen");
        }
        else if (chr_code == GLUE_VAL) {
            print_esc("skip");
        }
        else {
            print_esc("muskip");
        }
        break;
    // ~~~ End section 412 ~~~
    
    // ~~~ Section 417 ~~~
    case SET_AUX:
        if (chr_code == VMODE) {
            print_esc("prevdepth");
        }
        else {
            print_esc("spacefactor");
        }
        break;
    
    case SET_PAGE_INT:
        if (chr_code == 0) {
            print_esc("deadcycles");
        }
        else {
            print_esc("insertpenalties");
        }
        break;
    
    case SET_BOX_DIMEN:
        if (chr_code == WIDTH_OFFSET) {
            print_esc("wd");
        }
        else if (chr_code == HEIGHT_OFFSET) {
            print_esc("ht");
        }
        else {
            print_esc("dp");
        }
        break;
    
    case LAST_ITEM:
        switch (chr_code) {
        case INT_VAL:
            print_esc("lastpenalty");
            break;
        
        case DIMEN_VAL:
            print_esc("lastkern");
            break;
        
        case GLUE_VAL:
            print_esc("lastskip");
            break;
        
        case INPUT_LINE_NO_CODE:
            print_esc("inputlineno");
            break;
        
        default:
            print_esc("badness");
        }
        break;
    // ~~~ End section 417 ~~~
    
    // ~~~ Section 469 ~~~
    case CONVERT:
        switch (chr_code) {
        case NUMBER_CODE:
            print_esc("number");
            break;
        
        case ROMAN_NUMERAL_CODE:
            print_esc("romannumeral");
            break;
        
        case STRING_CODE:
            print_esc("string");
            break;
        
        case MEANING_CODE:
            print_esc("meaning");
            break;
        
        case FONT_NAME_CODE:
            print_esc("fontname");
            break;
        
        default:
            print_esc("jobname");
        }
        break;
    // ~~~ End section 469 ~~~
    
    // ~~~ Section 488 ~~~
    case IF_TEST:
        switch (chr_code) {
        case IF_CAT_CODE:
            print_esc("ifcat");
            break;
        
        case IF_INT_CODE:
            print_esc("ifnum");
            break;
        
        case IF_DIM_CODE:
            print_esc("ifdim");
            break;
        
        case IF_ODD_CODE:
            print_esc("ifodd");
            break;
        
        case IF_VMODE_CODE:
            print_esc("ifvmode");
            break;
        
        case IF_HMODE_CODE:
            print_esc("ifhmode");
            break;
        
        case IF_MMODE_CODE:
            print_esc("ifmmode");
            break;
        
        case IF_INNER_CODE:
            print_esc("ifinner");
            break;
        
        case IF_VOID_CODE:
            print_esc("ifvoid");
            break;
        
        case IF_HBOX_CODE:
            print_esc("ifhbox");
            break;
        
        case IF_VBOX_CODE:
            print_esc("ifvbox");
            break;
        
        case IFX_CODE:
            print_esc("ifx");
            break;
        
        case IF_EOF_CODE:
            print_esc("ifeof");
            break;
        
        case IF_TRUE_CODE:
            print_esc("iftrue");
            break;
        
        case IF_FALSE_CODE:
            print_esc("iffalse");
            break;
        
        case IF_CASE_CODE:
            print_esc("ifcase");
            break;
        
        default:
            print_esc("if");
        } 
        break;
    // ~~~ End section 488 ~~~
    
    // ~~~ Section 492 ~~~
    case FI_OR_ELSE:
        if (chr_code == FI_CODE) {
            print_esc("fi");
        }
        else if (chr_code == OR_CODE) {
            print_esc("or");
        }
        else {
            print_esc("else");
        }
        break;
    // ~~~ End section 492 ~~~
    
    // ~~~ Section 781 ~~~
    case TAB_MARK:
        if (chr_code == SPAN_CODE) {
            print_esc("span");
        }
        else {
            chr_cmd("alignment tab character ");
        }
        break;
    
    case CAR_RET:
        if (chr_code == CR_CODE) {
            print_esc("cr");
        }
        else {
            print_esc("crcr");
        }
        break;
    // ~~~ End section 781 ~~~
    
    // ~~~ Section 984 ~~~
    case SET_PAGE_DIMEN:
        switch (chr_code) {
        case 0:
            print_esc("pagegoal");
            break;
        
        case 1:
            print_esc("pagetotal");
            break;
    
        case 2:
            print_esc("pagestretch");
            break;
        
        case 3:
            print_esc("pagefilstretch");
            break;
    
        case 4:
            print_esc("pagefillstretch");
            break;
    
        case 5:
            print_esc("pagefilllstretch");
            break;
    
        case 6:
            print_esc("pageshrink");
            break;
        
        default:
            print_esc("pagedepth");
        }
    
        break;
    // ~~~ End section 984 ~~~
    
    // ~~~ Section 1053 ~~~
    case STOP:
        if (chr_code == 1) {
            print_esc("dump");
        }
        else {
            print_esc("end");
        }
        break;
    // ~~~ End section 1053 ~~~
    
    // ~~~ Section 1059 ~~~
    case HSKIP:
        switch (chr_code) {
        case SKIP_CODE:
            print_esc("hskip");
            break;
        
        case FIL_CODE:
            print_esc("hfil");
            break;
      
        case FILL_CODE:
            print_esc("hfill");
            break;
    
        case SS_CODE:
            print_esc("hss");
            break;
    
        default:
            print_esc("hfilneg");
        }
        break;
    
    case VSKIP:
        switch (chr_code) {
        case SKIP_CODE:
            print_esc("vskip");
            break;
        
        case FIL_CODE:
            print_esc("vfil");
            break;
        
        case FILL_CODE:
            print_esc("vfill");
            break;
        
        case SS_CODE:
            print_esc("vss");
            break;
        
        default:
            print_esc("vfilneg");
        }
        break;
    
    case MSKIP:
        print_esc("mskip");
        break;
    
    case KERN:
        print_esc("kern");
        break;
    
    case MKERN:
        print_esc("mkern");
        break;
    // ~~~ End section 1059 ~~~
    
    // ~~~ Section 1072 ~~~
    case HMOVE:
        if (chr_code == 1) {
            print_esc("moveleft");
        }
        else {
            print_esc("moveright");
        }
        break;
    
    case VMOVE:
        if (chr_code == 1) {
            print_esc("raise");
        }
        else {
            print_esc("lower");
        }
        break;
    
    case MAKE_BOX:
        switch (chr_code) {
        case BOX_CODE:
            print_esc("box");
            break;
      
        case COPY_CODE:
            print_esc("copy");
            break;
        
        case LAST_BOX_CODE:
            print_esc("lastbox");
            break;
      
        case VSPLIT_CODE:
            print_esc("vsplit");
            break;
      
        case VTOP_CODE:
            print_esc("vtop");
            break;
      
        case VTOP_CODE + VMODE:
            print_esc("vbox");
            break;
        
        default:
            print_esc("hbox");
        }
        break;
    
    case LEADER_SHIP:
        if (chr_code == A_LEADERS) {
            print_esc("leaders");
        }
        else if (chr_code == C_LEADERS) {
            print_esc("cleaders");
        }
        else if (chr_code == X_LEADERS) {
            print_esc("xleaders");
        }
        else {
            print_esc("shipout");
        }
        break;
    // ~~~ End section 1072 ~~~
    
    // ~~~ Section 1089 ~~~
    case START_PAR:
        if (chr_code == 0) {
            print_esc("noindent");
        }
        else {
            print_esc("indent");
        }
        break;
    // ~~~ End section 1089 ~~~
    
    // ~~~ Section 1108 ~~~
    case REMOVE_ITEM:
        if (chr_code == GLUE_NODE) {
            print_esc("unskip");
        }
        else if (chr_code == KERN_NODE) {
            print_esc("unkern");
        }
        else {
            print_esc("unpenalty");
        }
        break;
    
    case UN_HBOX:
        if (chr_code == COPY_CODE) {
            print_esc("unhcopy");
        }
        else {
            print_esc("unhbox");
        }
        break;
    
    case UN_VBOX:
        if (chr_code == COPY_CODE) {
            print_esc("unvcopy");
        }
        else {
            print_esc("unvbox");
        }
        break;
    // ~~~ End section 1108 ~~~
    
    // ~~~ Section 1115 ~~~
    case DISCRETIONARY:
        if (chr_code == 1) {
            print_esc("-");
        }
        else {
            print_esc("discretionary");
        }
        break;
    // ~~~ End section 1115 ~~~
    
    // ~~~ Section 1143 ~~~
    case EQ_NO:
        if (chr_code == 1) {
            print_esc("leqno");
        }
        else {
            print_esc("eqno");
        }
        break;
    // ~~~ End section 1143 ~~~
    
    // ~~~ Section 1157 ~~~
    case MATH_COMP:
        switch (chr_code) {
        case ORD_NOAD:
            print_esc("mathord");
            break;
        
        case OP_NOAD:
            print_esc("mathop");
            break;
        
        case BIN_NOAD:
            print_esc("mathbin");
            break;
    
        case REL_NOAD:
            print_esc("mathrel");
            break;
        
        case OPEN_NOAD:
            print_esc("mathopen");
            break;
        
        case CLOSE_NOAD:
            print_esc("mathclose");
            break;
        
        case PUNCT_NOAD:
            print_esc("mathpunct");
            break;
        
        case INNER_NOAD:
            print_esc("mathinner");
            break;
        
        case UNDER_NOAD:
            print_esc("underline");
            break;
        
        default:
            print_esc("overline");
        }
        break;
    
    case LIMIT_SWITCH:
        if (chr_code == LIMITS) {
            print_esc("limits");
        }
        else if (chr_code == NO_LIMITS) {
            print_esc("nolimits");
        }
        else {
            print_esc("displaylimits");
        }
        break;
    // ~~~ End section 1157 ~~~
    
    // ~~~ Section 1170 ~~~
    case MATH_STYLE:
        print_style(chr_code);
        break;
    // ~~~ End section 1170 ~~~
    
    // ~~~ Section 1179 ~~~
    case ABOVE:
        switch (chr_code) {
        case OVER_CODE:
            print_esc("over");
            break;
        
        case ATOP_CODE:
            print_esc("atop");
            break;
        
        case DELIMITED_CODE + ABOVE_CODE:
            print_esc("abovewithdelims");
            break;
        
        case DELIMITED_CODE + OVER_CODE:
            print_esc("overwithdelims");
            break;
        
        case DELIMITED_CODE + ATOP_CODE:
            print_esc("atopwithdelims");
            break;
        
        default:
            print_esc("above");
        }
        break;
    // ~~~ End section 1179 ~~~
    
    // ~~~ Section 1189 ~~~
    case LEFT_RIGHT:
        if (chr_code == LEFT_NOAD) {
            print_esc("left");
        }
        else {
            print_esc("right");
        }
        break;
    // ~~~ End section 1189 ~~~
    
    // ~~~ Section 1209 ~~~
    case PREFIX:
        if (chr_code == 1) {
            print_esc("long");
        }
        else if (chr_code == 2) {
            print_esc("outer");
        }
        else {
            print_esc("global");
        }
        break;
    
    case DEF:
        if (chr_code == 0) {
            print_esc("def");
        }
        else if (chr_code == 1) {
            print_esc("gdef");
        }
        else if (chr_code == 2) {
            print_esc("edef");
        }
        else {
            print_esc("xdef");
        }
        break;
    // ~~~ End section 1209 ~~~
    
    // ~~~ Section 1220 ~~~
    case LET:
        if (chr_code != NORMAL) {
            print_esc("futurelet");
        }
        else {
            print_esc("let");
        }
        break;
    // ~~~ End section 1220 ~~~
    
    // ~~~ Section 1223 ~~~
    case SHORTHAND_DEF:
        switch (chr_code) {
        case CHAR_DEF_CODE:
            print_esc("chardef");
            break;
        
        case MATH_CHAR_DEF_CODE:
            print_esc("mathchardef");
            break;
        
        case COUNT_DEF_CODE:
            print_esc("countdef");
            break;
        
        case DIMEN_DEF_CODE:
            print_esc("dimendef");
            break;
        
        case SKIP_DEF_CODE:
            print_esc("skipdef");
            break;
        
        case MU_SKIP_DEF_CODE:
            print_esc("muskipdef");
            break;
        
        default:
            print_esc("toksdef");
        }
        break;
    
    case CHAR_GIVEN:
        print_esc("char");
        print_hex(chr_code); 
        break;
    
    case MATH_GIVEN:
        print_esc("mathchar");
        print_hex(chr_code);
        break;
    // ~~~ End section 1223 ~~~
    
    // ~~~ Section 1231 ~~~
    case DEF_CODE:
        if (chr_code == CAT_CODE_BASE) {
            print_esc("catcode");
        }
        else if (chr_code == MATH_CODE_BASE) {
            print_esc("mathcode");
        }
        else if (chr_code == LC_CODE_BASE) {
            print_esc("lccode");
        }
        else if (chr_code == UC_CODE_BASE) {
            print_esc("uccode");
        }
        else if (chr_code == SF_CODE_BASE) {
            print_esc("sfcode");
        }
        else {
            print_esc("delcode");
        }
        break;
    
    case DEF_FAMILY:
        print_size(chr_code - MATH_FONT_BASE);
        break;
    // ~~~ End section 1231 ~~~
    
    // ~~~ Section 1251 ~~~
    case HYPH_DATA:
        if (chr_code == 1) {
            print_esc("patterns");
        }
        else {
            print_esc("hyphenation");
        }
        break;
    // ~~~ End section 1251 ~~~
    
    // ~~~ Section 1255 ~~~
    case ASSIGN_FONT_INT:
        if (chr_code == 0) {
            print_esc("hyphenchar");
        }
        else {
            print_esc("skewchar");
        }
        break;
    // ~~~ End section 1255 ~~~
    
    // ~~~ Section 1261 ~~~
    case SET_FONT:
        print("select font ");
        slow_print(font_name[chr_code]);
        if (font_size[chr_code] != font_dsize[chr_code]) {
            print(" at ");
            print_scaled(font_size[chr_code]);
            print("pt");
        }
        break;
    // ~~~ End section 1261 ~~~
    
    // ~~~ Section 1263 ~~~
    case SET_INTERACTION:
        switch (chr_code) {
        case BATCH_MODE:
            print_esc("batchmode");
            break;
      
        case NONSTOP_MODE:
            print_esc("nonstopmode");
            break;
        
        case SCROLL_MODE:
            print_esc("scrollmode");
            break;
        
        default:
            print_esc("errorstopmode");
        }
        break;
    // ~~~ End section 1263 ~~~
    
    // ~~~ Section 1273 ~~~
    case IN_STREAM:
        if (chr_code == 0) {
            print_esc("closein");
        }
        else {
            print_esc("openin");
        }
        break;
    // ~~~ End section 1273 ~~~
    
    // ~~~ Section 1278 ~~~
    case MESSAGE:
        if (chr_code == 0) {
            print_esc("message");
        }
        else {
            print_esc("errmessage");
        }
        break;
    // ~~~ End section 1278 ~~~
    
    // ~~~ Section 1287 ~~~
    case CASE_SHIFT:
        if (chr_code == LC_CODE_BASE) {
            print_esc("lowercase");
        }
        else {
            print_esc("uppercase");
        }
        break;
    // ~~~ End section 1287 ~~~
    
    // ~~~ Section 1292 ~~~
    case XRAY:
        switch (chr_code) {
        case SHOW_BOX_CODE:
            print_esc("showbox");
            break;
        
        case SHOW_THE_CODE:
            print_esc("showthe");
            break;
        
        case SHOW_LISTS_CODE:
            print_esc("showlists");
            break;
        
        default:
            print_esc("show");
        }
        break;
    // ~~~ End section 1292 ~~~
    
    // ~~~ Section 1295 ~~~
    case UNDEFINED_CS:
        print("undefined");
        break;
    
    case CALL:
        print("macro");
        break;
    
    case LONG_CALL:
        print_esc("long macro");
        break;
    
    case OUTER_CALL:
        print_esc("outer macro");
        break;
    
    case LONG_OUTER_CALL:
        print_esc("long");
        print_esc("outer macro");
        break;
    
    case END_TEMPLATE:
        print_esc("outer endtemplate");
        break;
    // ~~~ End section 1295 ~~~
    
    // ~~~ Section 1346 ~~~
    case EXTENSION:
        switch (chr_code) {
        case OPEN_NODE:
            print_esc("openout");
            break;
        
        case WRITE_NODE:
            print_esc("write");
            break;
        
        case CLOSE_NODE:
            print_esc("closeout");
            break;
        
        case SPECIAL_NODE:
            print_esc("special");
            break;
        
        case IMMEDIATE_CODE:
            print_esc("immediate");
            break;
        
        case SET_LANGUAGE_CODE:
            print_esc("setlanguage");
            break;
        
        default:
            print("[unknown extension!]");
        }
        break;
    // ~~~ End section 1346 ~~~
    // ~~~ End section 227 ~~~

    default:
        print("[unknown command code!]");
    }
}
// ~~~ End section 298 ~~~

// ~~~ Section 299 ~~~
void show_cur_cmd_chr() {
    begin_diagnostic();
    print_nl("{");
    if (mode != shown_mode) {
        print_mode(mode);
        print(": ");
        shown_mode = mode;
    }
    print_cmd_chr(cur_cmd, cur_chr);
    print_char('}');
    end_diagnostic(false);
}
// ~~~ End section 299 ~~~
