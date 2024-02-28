# Section 237

We can print the symbolic name of an integer parameter as follows.

```c io/other_printing.c
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
```
