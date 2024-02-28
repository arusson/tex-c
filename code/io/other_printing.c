// ~~~ Section 211 ~~~
// ~~~ Start file |other_printing.c|, 1382 ~~~
#include "arithmetic.h"
#include "builder.h"
#include "texerror.h"
#include "extensions.h"
#include "parser.h"
// ~~~ End section 1382 ~~~

// prints the mode represented by |m|
void print_mode(int m) {
    if (m > 0) {
        switch(m / (MAX_COMMAND + 1)) {
        case 0:
            print("vertical");
            break;
        
        case 1:
            print("horizontal");
            break;
        
        case 2:
            print("display math");
        }
    }
    else if (m == 0) {
        print("no");
    }
    else {
        switch ((-m) / (MAX_COMMAND + 1)) {
        case 0:
            print("internal vertical");
            break;
        
        case 1:
            print("restricted horizontal");
            break;
        
        case 2:
            print("math");
        }
    }
    print(" mode");
}
// ~~~ End section 211 ~~~

// ~~~ Section 218 ~~~
void show_activities() {
    int p;         // index into |nest|
    int m;         // mode
    memory_word a; // auxiliary
    pointer q, r;  // for showing the current page
    int t;         // ditto

    nest[nest_ptr] = cur_list; // put the top level into the array
    print_nl("");
    print_ln();
    for(p = nest_ptr; p >= 0; p--) {
        m = nest[p].mode_field;
        a = nest[p].aux_field;
        print_nl("### ");
        print_mode(m);
        print(" entered at line ");
        print_int(abs(nest[p].ml_field));
        if (m == HMODE && nest[p].pg_field != 0x830000) {
            print(" (language");
            print_int(nest[p].pg_field % 0x10000);
            print(":hyphenmin");
            print_int(nest[p].pg_field / 0x400000);
            print_char(',');
            print_int((nest[p].pg_field / 0x10000) % 64);
            print_char(')');
        }
        if (nest[p].ml_field < 0) {
            print(" (\\output routine)");
        }
        if (p == 0) {
            // ~~~ Show the status of the current page, 986 ~~~
            if (PAGE_HEAD != page_tail) {
                print_nl("### current page:");
                if (output_active) {
                    print(" (held over for next output)");
                }
                show_box(link(PAGE_HEAD));
                if (page_contents > EMPTY) {
                    print_nl("total height ");
                    print_totals();
                    print_nl(" goal height ");
                    print_scaled(page_goal);
                    r = link(PAGE_INS_HEAD);
                    while (r != PAGE_INS_HEAD) {
                        print_ln();
                        print_esc("insert");
                        t = subtype(r);
                        print_int(t);
                        print(" adds ");
                        if (count(t) == 1000) {
                            t = height(r);
                        }
                        else {
                            t = x_over_n(height(r), 1000)*count(t);
                        }
                        print_scaled(t);
                        if (type(r) == SPLIT_UP) {
                            q = PAGE_HEAD;
                            t = 0;
                            do {
                                q = link(q);
                                if (type(q) == INS_NODE && subtype(q) == subtype(r)) {
                                    incr(t);
                                }
                            } while (q != broken_ins(r));
                            print(", #");
                            print_int(t);
                            print(" might split");
                        }
                        r = link(r);
                    }
                }
            }
            // ~~~ End section 986 ~~~
            if (link(CONTRIB_HEAD) != null) {
                print_nl("### recent contributions:");
            }
        }
        show_box(link(nest[p].head_field));
        // ~~~ Show the auxiliary field, |a|, 219 ~~~
        switch(abs(m) / (MAX_COMMAND + 1)) {
        case 0:
            print_nl("prevdepth ");
            if (a.sc <= IGNORE_DEPTH) {
                print("ignored");
            }
            else {
                print_scaled(a.sc);
            }
            if (nest[p].pg_field != 0) {
                print(", prevgraf ");
                print_int(nest[p].pg_field);
                print(" line");
                if (nest[p].pg_field != 1) {
                    print_char('s');
                }
            }
            break;
        
        case 1:
            print_nl("spacefactor ");
            print_int(hh_lh(a));
            if (m > 0 && hh_rh(a) > 0) {
                print(", current language ");
                print_int(hh_rh(a));
            }
            break;
        
        case 2:
            if (a.integer != null) {
                print("this will begin denominator of:");
                show_box(a.integer);
            }
        } // there are no other cases
        // ~~~ End section 219 ~~~
    }
}
// ~~~ End section 218 ~~~

// ~~~ Section 225 ~~~
void print_skip_param(int n) {
    switch(n) {
    case LINE_SKIP_CODE:
        print_esc("lineskip");
        break;
    
    case BASELINE_SKIP_CODE:
        print_esc("baselineskip");
        break;
    
    case PAR_SKIP_CODE:
        print_esc("parskip");
        break;
    
    case ABOVE_DISPLAY_SKIP_CODE:
        print_esc("abovedisplayskip");
        break;
    
    case BELOW_DISPLAY_SKIP_CODE:
        print_esc("belowdisplayskip");
        break;
    
    case ABOVE_DISPLAY_SHORT_SKIP_CODE:
        print_esc("abovedisplayshortskip");
        break;
    
    case BELOW_DISPLAY_SHORT_SKIP_CODE:
        print_esc("belowdisplayshortskip");
        break;
    
    case LEFT_SKIP_CODE:
        print_esc("leftskip");
        break;
    
    case RIGHT_SKIP_CODE:
        print_esc("rightskip");
        break;
    
    case TOP_SKIP_CODE:
        print_esc("topskip");
        break;
    
    case SPLIT_TOP_SKIP_CODE:
        print_esc("splittopskip");
        break;
    
    case TAB_SKIP_CODE:
        print_esc("tabskip");
        break;
    
    case SPACE_SKIP_CODE:
        print_esc("spaceskip");
        break;
    
    case XSPACE_SKIP_CODE:
        print_esc("xspaceskip");
        break;
    
    case PAR_FILL_SKIP_CODE:
        print_esc("parfillskip");
        break;
    
    case THIN_MU_SKIP_CODE:
        print_esc("thinmuskip");
        break;
    
    case MED_MU_SKIP_CODE:
        print_esc("medmuskip");
        break;
    
    case THICK_MU_SKIP_CODE:
        print_esc("thickmuskip");
        break;
    
    default:
        print("[unknown glue parameter!]");
    }
}
// ~~~ End section 225 ~~~

// ~~~ Section 237 ~~~
void print_param(int n) {
    switch(n) {
    case PRETOLERANCE_CODE:
        print_esc("pretolerance");
        break;
    
    case TOLERANCE_CODE:
        print_esc("tolerance");
        break;
    
    case LINE_PENALTY_CODE:
        print_esc("linepenalty");
        break;
    
    case HYPHEN_PENALTY_CODE:
        print_esc("hyphenpenalty");
        break;
    
    case EX_HYPHEN_PENALTY_CODE:
        print_esc("exhyphenpenalty");
        break;
    
    case CLUB_PENALTY_CODE:
        print_esc("clubpenalty");
        break;
    
    case WIDOW_PENALTY_CODE:
        print_esc("widowpenalty");
        break;
    
    case DISPLAY_WIDOW_PENALTY_CODE:
        print_esc("displaywidowpenalty");
        break;
    
    case BROKEN_PENALTY_CODE:
        print_esc("brokenpenalty");
        break;
    
    case BIN_OP_PENALTY_CODE:
        print_esc("binoppenalty");
        break;
    
    case REL_PENALTY_CODE:
        print_esc("relpenalty");
        break;
    
    case PRE_DISPLAY_PENALTY_CODE:
        print_esc("predisplaypenalty");
        break;
    
    case POST_DISPLAY_PENALTY_CODE:
        print_esc("postdisplaypenalty");
        break;
    
    case INTER_LINE_PENALTY_CODE:
        print_esc("interlinepenalty");
        break;
    
    case DOUBLE_HYPHEN_DEMERITS_CODE:
        print_esc("doublehyphendemerits");
        break;
    
    case FINAL_HYPHEN_DEMERITS_CODE:
        print_esc("finalhyphendemerits");
        break;
    
    case ADJ_DEMERITS_CODE:
        print_esc("adjdemerits");
        break;
    
    case MAG_CODE:
        print_esc("mag");
        break;
    
    case DELIMITER_FACTOR_CODE:
        print_esc("delimiterfactor");
        break;
    
    case LOOSENESS_CODE:
        print_esc("looseness");
        break;
    
    case TIME_CODE:
        print_esc("time");
        break;
    
    case DAY_CODE:
        print_esc("day");
        break;
    
    case MONTH_CODE:
        print_esc("month");
        break;
    
    case YEAR_CODE:
        print_esc("year");
        break;
    
    case SHOW_BOX_BREADTH_CODE:
        print_esc("showboxbreadth");
        break;
    
    case SHOW_BOX_DEPTH_CODE:
        print_esc("showboxdepth");
        break;
    
    case HBADNESS_CODE:
        print_esc("hbadness");
        break;
    
    case VBADNESS_CODE:
        print_esc("vbadness");
        break;
    
    case PAUSING_CODE:
        print_esc("pausing");
        break;
    
    case TRACING_ONLINE_CODE:
        print_esc("tracingonline");
        break;
    
    case TRACING_MACROS_CODE:
        print_esc("tracingmacros");
        break;
    
    case TRACING_STATS_CODE:
        print_esc("tracingstats");
        break;
    
    case TRACING_PARAGRAPHS_CODE:
        print_esc("tracingparagraphs");
        break;
    
    case TRACING_PAGES_CODE:
        print_esc("tracingpages");
        break;
    
    case TRACING_OUTPUT_CODE:
        print_esc("tracingoutput");
        break;
    
    case TRACING_LOST_CHARS_CODE:
        print_esc("tracinglostchars");
        break;
    
    case TRACING_COMMANDS_CODE:
        print_esc("tracingcommands");
        break;
    
    case TRACING_RESTORES_CODE:
        print_esc("tracingrestores");
        break;
    
    case UC_HYPH_CODE:
        print_esc("uchyph");
        break;
    
    case OUTPUT_PENALTY_CODE:
        print_esc("outputpenalty");
        break;
    
    case MAX_DEAD_CYCLES_CODE:
        print_esc("maxdeadcycles");
        break;
    
    case HANG_AFTER_CODE:
        print_esc("hangafter");
        break;
    
    case FLOATING_PENALTY_CODE:
        print_esc("floatingpenalty");
        break;
    
    case GLOBAL_DEFS_CODE:
        print_esc("globaldefs");
        break;
    
    case CUR_FAM_CODE:
        print_esc("fam");
        break;
    
    case ESCAPE_CHAR_CODE:
        print_esc("escapechar");
        break;
    
    case DEFAULT_HYPHEN_CHAR_CODE:
        print_esc("defaulthyphenchar");
        break;
    
    case DEFAULT_SKEW_CHAR_CODE:
        print_esc("defaultskewchar");
        break;
    
    case END_LINE_CHAR_CODE:
        print_esc("endlinechar");
        break;
    
    case NEW_LINE_CHAR_CODE:
        print_esc("newlinechar");
        break;
    
    case LANGUAGE_CODE:
        print_esc("language");
        break;
    
    case LEFT_HYPHEN_MIN_CODE:
        print_esc("lefthyphenmin");
        break;
    
    case RIGHT_HYPHEN_MIN_CODE:
        print_esc("righthyphenmin");
        break;
    
    case HOLDING_INSERTS_CODE:
        print_esc("holdinginserts");
        break;
    
    case ERROR_CONTEXT_LINES_CODE:
        print_esc("errorcontextlines");
        break;
    
    default:
        print("[unknown integer parameter!]");
    }
}
// ~~~ End section 237 ~~~

// ~~~ Section 245 ~~~
// prepare to do some tracing
void begin_diagnostic() {
    old_setting = selector;
    if (tracing_online <= 0 && selector == TERM_AND_LOG) {
        decr(selector);
        if (history == SPOTLESS) {
            history = WARNING_ISSUED;
        }
    }
}

// restore proper conditions after tracing
void end_diagnostic(bool blank_line) {
    print_nl("");
    if (blank_line) {
        print_ln();
    }
    selector = old_setting;
}
// ~~~ End section 245 ~~~

// ~~~ Section 247 ~~~
void print_length_param(int n) {
    switch(n) {
    case PAR_INDENT_CODE:
        print_esc("parindent");
        break;
    
    case MATH_SURROUND_CODE:
        print_esc("mathsurround");
        break;
    
    case LINE_SKIP_LIMIT_CODE:
        print_esc("lineskiplimit");
        break;
    
    case HSIZE_CODE:
        print_esc("hsize");
        break;
    
    case VSIZE_CODE:
        print_esc("vsize");
        break;
    
    case MAX_DEPTH_CODE:
        print_esc("maxdepth");
        break;
    
    case SPLIT_MAX_DEPTH_CODE:
        print_esc("splitmaxdepth");
        break;
    
    case BOX_MAX_DEPTH_CODE:
        print_esc("boxmaxdepth");
        break;
    
    case HFUZZ_CODE:
        print_esc("hfuzz");
        break;
    
    case VFUZZ_CODE:
        print_esc("vfuzz");
        break;
    
    case DELIMITER_SHORTFALL_CODE:
        print_esc("delimitershortfall");
        break;
    
    case NULL_DELIMITER_SPACE_CODE:
        print_esc("nulldelimiterspace");
        break;
    
    case SCRIPT_SPACE_CODE:
        print_esc("scriptspace");
        break;
    
    case PRE_DISPLAY_SIZE_CODE:
        print_esc("predisplaysize");
        break;
    
    case DISPLAY_WIDTH_CODE:
        print_esc("displaywidth");
        break;
    
    case DISPLAY_INDENT_CODE:
        print_esc("displayindent");
        break;
    
    case OVERFULL_RULE_CODE:
        print_esc("overfullrule");
        break;
    
    case HANG_INDENT_CODE:
        print_esc("hangindent");
        break;
    
    case H_OFFSET_CODE:
        print_esc("hoffset");
        break;
    
    case V_OFFSET_CODE:
        print_esc("voffset");
        break;
    
    case EMERGENCY_STRETCH_CODE:
        print_esc("emergencystretch");
        break;
    
    default:
        print("[unknown dimen parameter!]");
    }
}
// ~~~ End section 247 ~~~

// ~~~ Section 252 ~~~
#ifdef STAT
void show_eqtb(pointer n) {
    if (n < ACTIVE_BASE) {
        print_char('?'); // this can't happen
    }
    else if (n <GLUE_BASE) {
        // ~~~ Show equivalent |n|, in region 1 or 2, 223 ~~~
        sprint_cs(n);
        print_char('=');
        print_cmd_chr(eq_type(n), equiv(n));
        if (eq_type(n) >= CALL) {
            print_char(':');
            show_token_list(link(equiv(n)), null, 32);
        }
        // ~~~ End section 223 ~~~
    }
    else if (n <LOCAL_BASE) {
        // ~~~ Show equivalent |n|, in region 3, 229 ~~~
        if (n < SKIP_BASE) {
            print_skip_param(n - GLUE_BASE);
            print_char('=');
            if (n < GLUE_BASE + THIN_MU_SKIP_CODE) {
                print_spec(equiv(n), "pt");
            }
            else {
                print_spec(equiv(n), "mu");
            }
        } 
        else if (n < MU_SKIP_BASE) {
          print_esc("skip");
          print_int(n - SKIP_BASE);
          print_char('=');
          print_spec(equiv(n), "pt");
        }
        else {
            print_esc("muskip");
            print_int(n - MU_SKIP_BASE);
            print_char('=');
            print_spec(equiv(n), "mu");
        }
        // ~~~ End section 229 ~~~
    }
    else if (n <INT_BASE) {
        // ~~~ Show equivalent |n|, in region 4, 233 ~~~
        if (n == PAR_SHAPE_LOC) {
            print_esc("parshape");
            print_char('=');
            if (par_shape_ptr == null) {
                print_char('0');
            }
            else {
                print_int(info(par_shape_ptr));
            }
        }
        else if (n < TOKS_BASE) {
          print_cmd_chr(ASSIGN_TOKS, n);
          print_char('=');
          if (equiv(n) != null) {
            show_token_list(link(equiv(n)), null, 32);
          }
        }
        else if (n < BOX_BASE) {
          print_esc("toks");
          print_int(n - TOKS_BASE);
          print_char('=');
          if (equiv(n) != null) {
            show_token_list(link(equiv(n)), null, 32);
          }
        }
        else if (n < CUR_FONT_LOC) {
          print_esc("box");
          print_int(n - BOX_BASE);
          print_char('=');
          if (equiv(n) == null) {
            print("void");
          }
          else {
            depth_threshold = 0;
            breadth_max = 1;
            show_node_list(equiv(n));
          }
        }
        else if (n < CAT_CODE_BASE) {
            // ~~~ Show the font identifier in |eqtb[n]|, 234 ~~~
            if (n == CUR_FONT_LOC) {
                print("current font");
            }
            else if (n < MATH_FONT_BASE + 16) {
                print_esc("textfont");
                print_int(n - MATH_FONT_BASE);
            }
            else if (n < MATH_FONT_BASE + 32) {
                print_esc("scriptfont");
                print_int(n - MATH_FONT_BASE - 16);
            }
            else  {
                print_esc("scriptscriptfont");
                print_int(n - MATH_FONT_BASE - 32);
            }
            print_char('=');
            print_esc_strnumber(hh_rh(hash[FONT_ID_BASE + equiv(n)])); // that's |font_id_text(equiv(n))|
            // ~~~ End section 234 ~~~
        }
        else {
            // ~~~ Show the halfword code in |eqtb[n]|, 235 ~~~
            if (n < MATH_CODE_BASE) {
              if (n < LC_CODE_BASE) {
                print_esc("catcode");
                print_int(n - CAT_CODE_BASE);
              }
              else if (n < UC_CODE_BASE) {
                print_esc("lccode");
                print_int(n - LC_CODE_BASE);
              }
              else if (n < SF_CODE_BASE) {
                print_esc("uccode");
                print_int(n - UC_CODE_BASE);
              }
              else {
                print_esc("sfcode");
                print_int(n - SF_CODE_BASE);
              }
              print_char('=');
              print_int(equiv(n));
            }
            else {
                print_esc("mathcode");
                print_int(n - MATH_CODE_BASE);
                print_char('=');
                print_int(ho(equiv(n)));
            }
            // ~~~ End section 235 ~~~
        }
        // ~~~ End section 233 ~~~
    }
    else if (n <DIMEN_BASE) {
        // ~~~ Show equivalent |n|, in region 5, 242 ~~~
        if (n < COUNT_BASE) {
            print_param(n - INT_BASE);
        }
        else if (n < DEL_CODE_BASE) {
            print_esc("count");
            print_int(n - COUNT_BASE);
        }
        else {
            print_esc("delcode");
            print_int(n - DEL_CODE_BASE);
        }
        print_char('=');
        print_int(eqtb[n].integer);
        // ~~~ End section 242 ~~~
    }
    else if (n <=EQTB_SIZE) {
        // ~~~ Show equivalent |n|, in region 6, 251 ~~~
        if (n < SCALED_BASE) {
            print_length_param(n - DIMEN_BASE);
        }
        else {
            print_esc("dimen");
            print_int(n - SCALED_BASE);
        }
        print_char('=');
        print_scaled(eqtb[n].sc);
        print("pt");
        // ~~~ End section 251 ~~~
    }
    else {
        print_char('?'); // this can't happen either
    }
}
#endif
// ~~~ End section 252 ~~~

// ~~~ Section 985 ~~~
void print_totals() {
    print_scaled(page_total);
    print_plus(2, "");
    print_plus(3, "fil");
    print_plus(4, "fill");
    print_plus(5, "filll");
    if (page_shrink != 0) {
        print(" minus ");
        print_scaled(page_shrink);
    }
}
// ~~~ End section 985 ~~~

// ~~~ Section 1293 ~~~
void show_whatever() {
    switch (cur_chr) {
    case SHOW_LISTS_CODE:
        begin_diagnostic();
        show_activities();
        break;
    
    case SHOW_BOX_CODE:
        // ~~~ Show the current contents of a box, 1296 ~~~
        scan_eight_bit_int();
        begin_diagnostic();
        print_nl("> \\box");
        print_int(cur_val);
        print_char('=');
        if (box(cur_val) == null) {
            print("void");
        }
        else {
            show_box(box(cur_val));
        }
        // ~~~ End section 1296 ~~~
        break;
    
    case SHOW_CODE:
        // ~~~ Show the current meaning of a token, then |goto common_ending|, 1294 ~~~
        get_token();
        print_nl("> ");
        if (cur_cs != 0) {
            sprint_cs(cur_cs);
            print_char('=');
        }
        print_meaning();
        goto common_ending;
        // ~~~ End section 1294 ~~~
    
    default:
        // ~~~ Show the current value of some parameter or register, then |goto common_ending|, 1297 ~~~
        the_toks();
        print_nl("> ");
        token_show(TEMP_HEAD);
        flush_list(link(TEMP_HEAD));
        goto common_ending;
        // ~~~ End section 1297 ~~~
    }
    // ~~~ Complete a potentially long \show command, 1298 ~~~
    end_diagnostic(true);
    print_err("OK");
    if (selector == TERM_AND_LOG && tracing_online <= 0) {
        selector = TERM_ONLY;
        print(" (see the transcript file)");
        selector = TERM_AND_LOG;
    }
    // ~~~ End section 1298 ~~~
common_ending:
    if (interaction < ERROR_STOP_MODE) {
        help0;
        decr(error_count);
    }
    else if (tracing_online > 0) {
        help3("This isn't an error message; I'm just \\showing something.")
            ("Type `I\\show...' to show more (e.g., \\show\\cs,")
            ("\\showthe\\count10, \\showbox255, \\showlists).");
    }
    else {
        help5("This isn't an error message; I'm just \\showing something.")
            ("Type `I\\show...' to show more (e.g., \\show\\cs,")
            ("\\showthe\\count10, \\showbox255, \\showlists).")
            ("And type `I\\tracingonline = 1\\show...' to show boxes and")
            ("lists on your terminal as well as in the transcript file.");
    }
    error();
}
// ~~~ End section 1293 ~~~

// ~~~ Section 1355 ~~~
void print_write_whatsit(char *s, pointer p) {
    print_esc(s);
    if (write_stream(p) < 16) {
        print_int(write_stream(p));
    }
    else if (write_stream(p) == 16) {
        print_char('*');
    }
    else {
        print_char('-');
    }
}
// ~~~ End section 1355 ~~~
