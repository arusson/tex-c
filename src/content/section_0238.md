# Section 238

The integer parameter names must be entered into the hash table.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("pretolerance", ASSIGN_INT, INT_BASE + PRETOLERANCE_CODE);
primitive("tolerance", ASSIGN_INT, INT_BASE + TOLERANCE_CODE);
primitive("linepenalty", ASSIGN_INT, INT_BASE + LINE_PENALTY_CODE);
primitive("hyphenpenalty", ASSIGN_INT, INT_BASE + HYPHEN_PENALTY_CODE);
primitive("exhyphenpenalty", ASSIGN_INT, INT_BASE + EX_HYPHEN_PENALTY_CODE);
primitive("clubpenalty", ASSIGN_INT, INT_BASE + CLUB_PENALTY_CODE);
primitive("widowpenalty", ASSIGN_INT, INT_BASE + WIDOW_PENALTY_CODE);
primitive("displaywidowpenalty",  ASSIGN_INT, INT_BASE + DISPLAY_WIDOW_PENALTY_CODE);
primitive("brokenpenalty", ASSIGN_INT, INT_BASE + BROKEN_PENALTY_CODE);
primitive("binoppenalty", ASSIGN_INT, INT_BASE + BIN_OP_PENALTY_CODE);
primitive("relpenalty", ASSIGN_INT, INT_BASE + REL_PENALTY_CODE);
primitive("predisplaypenalty", ASSIGN_INT, INT_BASE + PRE_DISPLAY_PENALTY_CODE);
primitive("postdisplaypenalty", ASSIGN_INT, INT_BASE + POST_DISPLAY_PENALTY_CODE);
primitive("interlinepenalty", ASSIGN_INT, INT_BASE + INTER_LINE_PENALTY_CODE);
primitive("doublehyphendemerits",  ASSIGN_INT, INT_BASE + DOUBLE_HYPHEN_DEMERITS_CODE);
primitive("finalhyphendemerits",  ASSIGN_INT, INT_BASE + FINAL_HYPHEN_DEMERITS_CODE);
primitive("adjdemerits", ASSIGN_INT, INT_BASE + ADJ_DEMERITS_CODE);
primitive("mag", ASSIGN_INT, INT_BASE + MAG_CODE);
primitive("delimiterfactor", ASSIGN_INT, INT_BASE + DELIMITER_FACTOR_CODE);
primitive("looseness", ASSIGN_INT, INT_BASE + LOOSENESS_CODE);
primitive("time", ASSIGN_INT, INT_BASE + TIME_CODE);
primitive("day", ASSIGN_INT, INT_BASE + DAY_CODE);
primitive("month", ASSIGN_INT, INT_BASE + MONTH_CODE);
primitive("year", ASSIGN_INT, INT_BASE + YEAR_CODE);
primitive("showboxbreadth", ASSIGN_INT, INT_BASE + SHOW_BOX_BREADTH_CODE);
primitive("showboxdepth", ASSIGN_INT, INT_BASE + SHOW_BOX_DEPTH_CODE);
primitive("hbadness", ASSIGN_INT, INT_BASE + HBADNESS_CODE);
primitive("vbadness", ASSIGN_INT, INT_BASE + VBADNESS_CODE);
primitive("pausing", ASSIGN_INT, INT_BASE + PAUSING_CODE);
primitive("tracingonline", ASSIGN_INT, INT_BASE + TRACING_ONLINE_CODE);
primitive("tracingmacros", ASSIGN_INT, INT_BASE + TRACING_MACROS_CODE);
primitive("tracingstats", ASSIGN_INT, INT_BASE + TRACING_STATS_CODE);
primitive("tracingparagraphs", ASSIGN_INT, INT_BASE + TRACING_PARAGRAPHS_CODE);
primitive("tracingpages", ASSIGN_INT, INT_BASE + TRACING_PAGES_CODE);
primitive("tracingoutput", ASSIGN_INT, INT_BASE + TRACING_OUTPUT_CODE);
primitive("tracinglostchars", ASSIGN_INT, INT_BASE + TRACING_LOST_CHARS_CODE);
primitive("tracingcommands", ASSIGN_INT, INT_BASE + TRACING_COMMANDS_CODE);
primitive("tracingrestores", ASSIGN_INT, INT_BASE + TRACING_RESTORES_CODE);
primitive("uchyph", ASSIGN_INT, INT_BASE + UC_HYPH_CODE);
primitive("outputpenalty", ASSIGN_INT, INT_BASE + OUTPUT_PENALTY_CODE);
primitive("maxdeadcycles", ASSIGN_INT, INT_BASE + MAX_DEAD_CYCLES_CODE);
primitive("hangafter", ASSIGN_INT, INT_BASE + HANG_AFTER_CODE);
primitive("floatingpenalty", ASSIGN_INT, INT_BASE + FLOATING_PENALTY_CODE);
primitive("globaldefs", ASSIGN_INT, INT_BASE + GLOBAL_DEFS_CODE);
primitive("fam", ASSIGN_INT, INT_BASE + CUR_FAM_CODE);
primitive("escapechar", ASSIGN_INT, INT_BASE + ESCAPE_CHAR_CODE);
primitive("defaulthyphenchar", ASSIGN_INT, INT_BASE + DEFAULT_HYPHEN_CHAR_CODE);
primitive("defaultskewchar", ASSIGN_INT, INT_BASE + DEFAULT_SKEW_CHAR_CODE);
primitive("endlinechar", ASSIGN_INT, INT_BASE + END_LINE_CHAR_CODE);
primitive("newlinechar", ASSIGN_INT, INT_BASE + NEW_LINE_CHAR_CODE);
primitive("language", ASSIGN_INT, INT_BASE + LANGUAGE_CODE);
primitive("lefthyphenmin", ASSIGN_INT, INT_BASE + LEFT_HYPHEN_MIN_CODE);
primitive("righthyphenmin", ASSIGN_INT, INT_BASE + RIGHT_HYPHEN_MIN_CODE);
primitive("holdinginserts", ASSIGN_INT, INT_BASE + HOLDING_INSERTS_CODE);
primitive("errorcontextlines", ASSIGN_INT, INT_BASE + ERROR_CONTEXT_LINES_CODE);
```
