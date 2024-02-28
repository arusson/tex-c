# Section 236

Region 5 of *eqtb* contains the integer parameters and registers defined here, as well as the *DEL_CODE* table.
The latter table differs from the *CAT_CODE .. MATH_CODE* tables that precede it, since delimiter codes are fullword integers while the other kinds of codes occupy at most a halfword.
This is what makes region 5 different from region 4.
We will store the *eq_level* information in an auxiliary array of quarterwords that will be defined later.

> ![NOTE]
> *time* is defined as *time_* to avoid conflict with *time* from file `time.h` used to get local time.

```c include/constants.h
#define PRETOLERANCE_CODE           0        // badness tolerance before hyphenation
#define TOLERANCE_CODE              1        // badness tolerance after hyphenation
#define LINE_PENALTY_CODE           2        // added to the badness of every line
#define HYPHEN_PENALTY_CODE         3        // penalty for break after discretionary hyphen
#define EX_HYPHEN_PENALTY_CODE      4        // penalty for break after explicit hyphen
#define CLUB_PENALTY_CODE           5        // penalty for creating a club line
#define WIDOW_PENALTY_CODE          6        // penalty for creating a widow line
#define DISPLAY_WIDOW_PENALTY_CODE  7        // ditto, just before a display
#define BROKEN_PENALTY_CODE         8        // penalty for breaking a page at a broken line
#define BIN_OP_PENALTY_CODE         9        // penalty for breaking after a binary operation
#define REL_PENALTY_CODE            10       // penalty for breaking after a relation
#define PRE_DISPLAY_PENALTY_CODE    11       // penalty for breaking just before a displayed formula
#define POST_DISPLAY_PENALTY_CODE   12       // penalty for breaking just after a displayed formula
#define INTER_LINE_PENALTY_CODE     13       // additional penalty between lines
#define DOUBLE_HYPHEN_DEMERITS_CODE 14       // demerits for double hyphen break
#define FINAL_HYPHEN_DEMERITS_CODE  15       // demerits for final hyphen break
#define ADJ_DEMERITS_CODE           16       // demerits for adjacent incompatible lines
#define MAG_CODE                    17       // magnification ratio
#define DELIMITER_FACTOR_CODE       18       // ratio for variable-size delimiters
#define LOOSENESS_CODE              19       // change in number of lines for a paragraph
#define TIME_CODE                   20       // current time of day
#define DAY_CODE                    21       // current day of the month
#define MONTH_CODE                  22       // current month of the year
#define YEAR_CODE                   23       // current year of our Lord
#define SHOW_BOX_BREADTH_CODE       24       // nodes per level in |show_box|
#define SHOW_BOX_DEPTH_CODE         25       // maximum level in |show_box|
#define HBADNESS_CODE               26       // hboxes exceeding this badness will be shown by |hpack|
#define VBADNESS_CODE               27       // vboxes exceeding this badness will be shown by |vpack|
#define PAUSING_CODE                28       // pause after each line is read from a file
#define TRACING_ONLINE_CODE         29       // show diagnostic output on terminal
#define TRACING_MACROS_CODE         30       // show macros as they are being expanded
#define TRACING_STATS_CODE          31       // show memory usage if TeX knows it
#define TRACING_PARAGRAPHS_CODE     32       // show line-break calculations
#define TRACING_PAGES_CODE          33       // show page-break calculations
#define TRACING_OUTPUT_CODE         34       // show boxes when they are shipped out
#define TRACING_LOST_CHARS_CODE     35       // show characters that aren't in the font
#define TRACING_COMMANDS_CODE       36       // show command codes at |big_switch|
#define TRACING_RESTORES_CODE       37       // show equivalents when they are restored
#define UC_HYPH_CODE                38       // hyphenate words beginning with a capital letter
#define OUTPUT_PENALTY_CODE         39       // penalty found at current page break
#define MAX_DEAD_CYCLES_CODE        40       // bound on consecutive dead cycles of output
#define HANG_AFTER_CODE             41       // hanging indentation changes after this many lines
#define FLOATING_PENALTY_CODE       42       // penalty for insertions held over after a split
#define GLOBAL_DEFS_CODE            43       // override \global specifications
#define CUR_FAM_CODE                44       // current family
#define ESCAPE_CHAR_CODE            45       // escape character for token output
#define DEFAULT_HYPHEN_CHAR_CODE    46       // value of \hyphenchar when a font is loaded
#define DEFAULT_SKEW_CHAR_CODE      47       // value of \skewchar when a font is loaded
#define END_LINE_CHAR_CODE          48       // character placed at the right end of the buffer
#define NEW_LINE_CHAR_CODE          49       // character that prints as |print_ln|
#define LANGUAGE_CODE               50       // current hyphenation table
#define LEFT_HYPHEN_MIN_CODE        51       // minimum left hyphenation fragment size
#define RIGHT_HYPHEN_MIN_CODE       52       // minimum right hyphenation fragment size
#define HOLDING_INSERTS_CODE        53       // do not remove insertion nodes from \box255
#define ERROR_CONTEXT_LINES_CODE    54       // maximum intermediate line pairs shown
#define INT_PARS                    55       // total number of integer parameters
#define COUNT_BASE    (INT_BASE + INT_PARS)  // 256 user \count registers
#define DEL_CODE_BASE (COUNT_BASE + 256)     // 256 delimiter code mappings
#define DIMEN_BASE    (DEL_CODE_BASE + 256)  // beginning of region 6
```

```c include/datastructures.h
#define del_code(X)              eqtb[DEL_CODE_BASE + (X)].integer
#define count(X)                 eqtb[COUNT_BASE + (X)].integer
#define int_par(X)               eqtb[INT_BASE + (X)].integer // an integer parameter
#define pretolerance             int_par(PRETOLERANCE_CODE)
#define tolerance                int_par(TOLERANCE_CODE)
#define line_penalty             int_par(LINE_PENALTY_CODE)
#define hyphen_penalty           int_par(HYPHEN_PENALTY_CODE)
#define ex_hyphen_penalty        int_par(EX_HYPHEN_PENALTY_CODE)
#define club_penalty             int_par(CLUB_PENALTY_CODE)
#define widow_penalty            int_par(WIDOW_PENALTY_CODE)
#define display_widow_penalty    int_par(DISPLAY_WIDOW_PENALTY_CODE)
#define broken_penalty           int_par(BROKEN_PENALTY_CODE)
#define bin_op_penalty           int_par(BIN_OP_PENALTY_CODE)
#define rel_penalty              int_par(REL_PENALTY_CODE)
#define pre_display_penalty      int_par(PRE_DISPLAY_PENALTY_CODE)
#define post_display_penalty     int_par(POST_DISPLAY_PENALTY_CODE)
#define inter_line_penalty       int_par(INTER_LINE_PENALTY_CODE)
#define double_hyphen_demerits   int_par(DOUBLE_HYPHEN_DEMERITS_CODE)
#define final_hyphen_demerits    int_par(FINAL_HYPHEN_DEMERITS_CODE)
#define adj_demerits             int_par(ADJ_DEMERITS_CODE)
#define mag                      int_par(MAG_CODE)
#define delimiter_factor         int_par(DELIMITER_FACTOR_CODE)
#define looseness                int_par(LOOSENESS_CODE)
#define time_                    int_par(TIME_CODE)
#define day                      int_par(DAY_CODE)
#define month                    int_par(MONTH_CODE)
#define year                     int_par(YEAR_CODE)
#define show_box_breadth         int_par(SHOW_BOX_BREADTH_CODE)
#define show_box_depth           int_par(SHOW_BOX_DEPTH_CODE)
#define hbadness                 int_par(HBADNESS_CODE)
#define vbadness                 int_par(VBADNESS_CODE)
#define pausing                  int_par(PAUSING_CODE)
#define tracing_online           int_par(TRACING_ONLINE_CODE)
#define tracing_macros           int_par(TRACING_MACROS_CODE)
#define tracing_stats            int_par(TRACING_STATS_CODE)
#define tracing_paragraphs       int_par(TRACING_PARAGRAPHS_CODE)
#define tracing_pages            int_par(TRACING_PAGES_CODE)
#define tracing_output           int_par(TRACING_OUTPUT_CODE)
#define tracing_lost_chars       int_par(TRACING_LOST_CHARS_CODE)
#define tracing_commands         int_par(TRACING_COMMANDS_CODE)
#define tracing_restores         int_par(TRACING_RESTORES_CODE)
#define uc_hyph                  int_par(UC_HYPH_CODE)
#define output_penalty           int_par(OUTPUT_PENALTY_CODE)
#define max_dead_cycles          int_par(MAX_DEAD_CYCLES_CODE)
#define hang_after               int_par(HANG_AFTER_CODE)
#define floating_penalty         int_par(FLOATING_PENALTY_CODE)
#define global_defs              int_par(GLOBAL_DEFS_CODE)
#define cur_fam                  int_par(CUR_FAM_CODE)
#define escape_char              int_par(ESCAPE_CHAR_CODE)
#define default_hyphen_char      int_par(DEFAULT_HYPHEN_CHAR_CODE)
#define default_skew_char        int_par(DEFAULT_SKEW_CHAR_CODE)
#define end_line_char            int_par(END_LINE_CHAR_CODE)
#define new_line_char            int_par(NEW_LINE_CHAR_CODE)
#define language                 int_par(LANGUAGE_CODE)
#define left_hyphen_min          int_par(LEFT_HYPHEN_MIN_CODE)
#define right_hyphen_min         int_par(RIGHT_HYPHEN_MIN_CODE)
#define holding_inserts          int_par(HOLDING_INSERTS_CODE)
#define error_context_lines      int_par(ERROR_CONTEXT_LINES_CODE)
```

```c << Assign the values |depth_threshold = show_box_depth| and |breadth_max = show_box_breadth| >>=
depth_threshold = show_box_depth;
breadth_max = show_box_breadth;
```
