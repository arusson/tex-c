// ~~~ Section 2 ~~~
// ~~~ Start file |constants.h|, 1381 ~~~
#ifndef CONSTANTS_H_
#define CONSTANTS_H_
// ~~~ End section 1381 ~~~

#define BANNER "This is TeX, Version 3.141592653" // printed when TeX starts
// ~~~ End section 2 ~~~

// ~~~ Section 11 ~~~
#ifdef TRIP
#define MEM_MAX         3000
#define MEM_MIN         1
#else
#define MEM_MAX         30000 // greatest index in TeX's internal |mem| array; must be strictly less than |MAX_HALFWORD|; must be equal to |MEM_TOP| in INITEX, otherwise |>= MEM_TOP|
#define MEM_MIN         0     // smallest index in TeX's internal |mem| array; must be |MIN_HALFWORD| or more; must be equal to |MEM_BOT| in INITEX, otherwise |<= MEM_BOT|
#endif

#define BUF_SIZE        200000// maximum number of characters simultaneously present in current lines of open files and in control sequences between \csname and \endcsname; must not exceed |MAX_HALFWORD|

#ifdef TRIP
#define ERROR_LINE      64
#define HALF_ERROR_LINE 32
#define MAX_PRINT_LINE  72
#else
#define ERROR_LINE      72    // width of context lines on terminal error messages 
#define HALF_ERROR_LINE 42    // width of first lines of contexts in terminal error messages; should be between 30 and |ERROR_LINE - 15|
#define MAX_PRINT_LINE  79    // width of longest text lines output; should be at least 60
#endif

#define STACK_SIZE      200   // maximum number of simultaneous input sources
#define MAX_IN_OPEN     6     // maximum number of input files and error insertions that can be going on simultaneously
#define FONT_MAX        75    // maximum internal font number; must not exceed |MAX_QUARTERWORD| and must be at most |FONT_BASE + 256|
#define FONT_MEM_SIZE   20000 // number of words of |font_info| for all fonts
#define PARAM_SIZE      60    // maximum number of simultaneous macro parameters
#define NEST_SIZE       40    // maximum number of semantic levels simultaneously active
#define MAX_STRINGS     3000  // maximum number of strings; must not exceed |MAX_HALFWORD|
#define POOL_SIZE       32000 // maximum number of characters in strings, including all error messages and help texts, and the names of all fonts and control sequences;
#define SAVE_SIZE       600   // space for saving values outside of current group; must be at most |MAX_HALFWORD|
#define TRIE_SIZE       8000  // space for hyphenation patterns; should be larger for INITEX than it is in production versions of TeX
#define TRIE_OP_SIZE    500   // space for "opcodes" in the hyphenation patterns
#define DVI_BUF_SIZE    800   // size of the output buffer; must be a multiple of 8
#define FILE_NAME_SIZE  40    // file names shouldn't be longer than this
// ~~~ End section 11 ~~~

// ~~~ Section 12 ~~~
#ifdef TRIP
#define MEM_BOT    1
#define MEM_TOP    3000
#else
#define MEM_BOT    0     // smallest index in the |mem| array dumped by INITEX must not be less than |MEM_MIN|
#define MEM_TOP    30000 // largest index in the |mem| array dumped by INITEX; must be substantially larger than |MEM_BOT| and not greater than |MEM_MAX|
#endif

#define FONT_BASE  0     // smallest internal font number; must not be less than |MIN_QUARTERWORD|
#define HASH_SIZE  2100  // maximum number of control sequences; it should be at most about |(MEM_MAX - MEM_MIN)/10|
#define HASH_PRIME 1777  // a prime number equal to about 85% of |HASH_SIZE|
#define HYPH_SIZE  307   // another prime; the number of \hyphenation exceptions
// ~~~ End section 12 ~~~

// ~~~ Section 16 ~~~
#define EMPTY 0 // symbolic name for a null constant
// ~~~ End section 16 ~~~

// ~~~ Section 19 ~~~
#define FIRST_TEXT_CHAR 0   // ordinal number of the smallest element of |text_char|
#define LAST_TEXT_CHAR  255 // ordinal number of the largest element of |text_char|
// ~~~ End section 19 ~~~

// ~~~ Section 22 ~~~
#define NULL_CODE       0   // ASCII code that might disappear
#define CARRIAGE_RETURN 13  // ASCII code used at end of line
#define INVALID_CODE    127 // ASCII code that many systems prohibit in text files
// ~~~ End section 22 ~~~

// ~~~ Section 51 ~~~
// ~~~ Internal strings numbers in the pool, 51 ~~~
#define EMPTY_STRING 256 // ""

// ~~~ Section 258 ~~~
#define NOTEXPANDED_STRING 257
// ~~~ End section 258 ~~~

// ~~~ Section 514 ~~~
#define TEX_AREA 258
#define TEX_FONT_AREA 259
// ~~~ End section 514 ~~~

// ~~~ Section 520 ~~~
#define FMT_EXT 260
// ~~~ End section 520 ~~~

// ~~~ Section 530 ~~~
#define TEX_EXT 261
// ~~~ End section 530 ~~~

// ~~~ Section 532 ~~~
#define DVI_EXT 262
// ~~~ End section 532 ~~~

// ~~~ Section 534 ~~~
#define TEXPUT_STRING 263
#define LOG_EXT       264
// ~~~ End section 534 ~~~

// ~~~ Section 552 ~~~
#define NULLFONT_STRING 265
// ~~~ End section 552 ~~~

// ~~~ Section 563 ~~~
#define TFM_EXT 266
// ~~~ End section 563 ~~~

// ~~~ Section 780 ~~~
#define ENDTEMPLATE_STRING 267
// ~~~ End section 780 ~~~

// ~~~ Section 1216 ~~~
#define INACCESSIBLE_STRING 268
// ~~~ End section 1216 ~~~

// ~~~ Section 1257 ~~~
#define FONT_STRING 269
// ~~~ End section 1257 ~~~

// ~~~ Section 1301 ~~~
#define INITEX_IDENT_STRING 270
// ~~~ End section 1301 ~~~

// ~~~ Section 1369 ~~~
#define ENDWRITE_STRING 271
// ~~~ End section 1369 ~~~
// ~~~ End section 51 ~~~
// ~~~ End section 51 ~~~

// ~~~ Section 54 ~~~
#define NO_PRINT     16 // |selector| setting that makes data disappear
#define TERM_ONLY    17 // printing is destined for the terminal only
#define LOG_ONLY     18 // printing is destined for the transcript file only
#define TERM_AND_LOG 19 // normal |selector| setting
#define PSEUDO       20 // special |selector| setting for |show_context|
#define NEW_STRING   21 // printing is deflected to the string pool
#define MAX_SELECTOR 21 // highest selector setting
// ~~~ End section 54 ~~~

// ~~~ Section 73 ~~~
#define BATCH_MODE      0 // omits all stops and omits terminal output
#define NONSTOP_MODE    1 // omits all stops
#define SCROLL_MODE     2 // omits error stops
#define ERROR_STOP_MODE 3 // stops at every opportunity to interact
// ~~~ End section 73 ~~~

// ~~~ Section 76 ~~~
#define SPOTLESS             0 // |history| value when nothing has been amiss yet
#define WARNING_ISSUED       1 // |history| value when |begin_diagnostic| has been called
#define ERROR_MESSAGE_ISSUED 2 // |history| value when |error| has been called
#define FATAL_ERROR_STOP     3 // |history| value when termination was premature
// ~~~ End section 76 ~~~

// ~~~ Section 101 ~~~
#define UNITY 65536  // 2^{16}, represents 1.00000
#define TWO   131072 // 2^{17}, represents 2.00000
// ~~~ End section 101 ~~~

// ~~~ Section 108 ~~~
#define INF_BAD 10000 // infinitely bad value
// ~~~ End section 108 ~~~

// ~~~ Section 110 ~~~
#define MIN_QUARTERWORD 0           // smallest allowable value in a |quarterword|
#define MAX_QUARTERWORD 65535       // largest allowable value in a |quarterword|
#define MIN_HALFWORD    -0x3fffffff // smallest allowable value in a |halfword|
#define MAX_HALFWORD    0x3fffffff  // largest allowable value in a |halfword|
// ~~~ End section 110 ~~~

// ~~~ Section 115 ~~~
#define null MIN_HALFWORD // the null pointer
// ~~~ End section 115 ~~~

// ~~~ Section 124 ~~~
#define EMPTY_FLAG MAX_HALFWORD // the |link| of an empty variable-size node
// ~~~ End section 124 ~~~

// ~~~ Section 135 ~~~
#define HLIST_NODE    0 // |type| of hlist nodes
#define BOX_NODE_SIZE 7 // number of words to allocate for a box node
#define WIDTH_OFFSET  1 // position of |width| field in a box node
#define DEPTH_OFFSET  2 // position of |depth| field in a box node
#define HEIGHT_OFFSET 3 // position of |height| field in a box node
#define LIST_OFFSET   5 // position of |list_ptr| field in a box node
#define NORMAL        0 // the most common case when several cases are named
#define STRETCHING    1 // glue setting applies to the stretch components
#define SHRINKING     2 // glue setting applies to the shrink components
#define GLUE_OFFSET   6 // position of |glue_set| in a box node
// ~~~ End section 135 ~~~

// ~~~ Section 137 ~~~
#define VLIST_NODE 1 // |type| of vlist nodes
// ~~~ End section 137 ~~~

// ~~~ Section 138 ~~~
#define RULE_NODE 2           // |type| of rule nodes
#define RULE_NODE_SIZE 4      // number of words to allocate for a rule node
#define NULL_FLAG -0x40000000 // -2^{30}, signifies a missing item
// ~~~ End section 138 ~~~

// ~~~ Section 140 ~~~
#define INS_NODE      3 // |type| of insertion nodes
#define INS_NODE_SIZE 5 // number of words to allocate for an insertion
// ~~~ End section 140 ~~~

// ~~~ Section 141 ~~~
#define MARK_NODE       4 // |type| of a mark node
#define SMALL_NODE_SIZE 2 // number of words to allocate for most node types
// ~~~ End section 141 ~~~

// ~~~ Section 142 ~~~
#define ADJUST_NODE 5 // |type| of an adjust node
// ~~~ End section 142 ~~~

// ~~~ Section 143 ~~~
#define LIGATURE_NODE 6 // |type| of a ligature node
// ~~~ End section 143 ~~~

// ~~~ Section 145 ~~~
#define DISC_NODE 7 // |type| of a discretionary node
// ~~~ End section 145 ~~~

// ~~~ Section 146 ~~~
#define WHATSIT_NODE 8 // |type| of special extension nodes
// ~~~ End section 146 ~~~

// ~~~ Section 147 ~~~
#define MATH_NODE 9 // |type| of a math node
#define BEFORE    0 // |subtype| for math node that introduces a formula
#define AFTER     1 // |subtype| for math node that winds up a formula
// ~~~ End section 147 ~~~

// ~~~ Section 149 ~~~
#define GLUE_NODE      10  // |type| of node that points to a glue specification
#define COND_MATH_GLUE 98  // special |subtype| to suppress glue in the next node
#define MU_GLUE        99  // |subtype| for math glue
#define A_LEADERS      100 // |subtype| for aligned leaders
#define C_LEADERS      101 // |subtype| for centered leaders
#define X_LEADERS      102 // |subtype| for expanded leaders
// ~~~ End section 149 ~~~

// ~~~ Section 150 ~~~
#define GLUE_SPEC_SIZE 4 // number of words to allocate for a glue specification
#define FIL            1 // first-order infinity
#define FILL           2 // second-order infinity
#define FILLL          3 // third-order infinity
// ~~~ End section 150 ~~~

// ~~~ Section 155 ~~~
#define KERN_NODE 11 // |type| of a kern node
#define EXPLICIT  1  // |subtype| of kern nodes from \kern and \/
#define ACC_KERN  2  // |subtype| of kern nodes from accents
// ~~~ End section 155 ~~~

// ~~~ Section 157 ~~~
#define PENALTY_NODE  12             // |type| of a penalty node
#define INF_PENALTY   INF_BAD        // "infinite" penalty value
#define EJECT_PENALTY (-INF_PENALTY) // "negatively infinite" penalty value
// ~~~ End section 157 ~~~

// ~~~ Section 159 ~~~
#define UNSET_NODE 13 // |type| for an unset node
// ~~~ End section 159 ~~~

// ~~~ Section 162 ~~~
#define ZERO_GLUE       MEM_BOT                      // specification for 0pt plus 0pt minus 0pt
#define FIL_GLUE        (ZERO_GLUE + GLUE_SPEC_SIZE) // 0pt plus 1fil minus 0pt
#define FILL_GLUE       (FIL_GLUE + GLUE_SPEC_SIZE)  // 0pt plus 1fill minus 0pt
#define SS_GLUE         (FILL_GLUE + GLUE_SPEC_SIZE) // 0pt plus 1fil minus 1fil
#define FIL_NEG_GLUE    (SS_GLUE + GLUE_SPEC_SIZE)   // 0pt plus -1fil minus 0pt
// largest statically allocated word in the variable-size |mem|
#define LO_MEM_STAT_MAX (FIL_NEG_GLUE + GLUE_SPEC_SIZE - 1) 

#define PAGE_INS_HEAD     MEM_TOP        // list of insertion data for current page
#define CONTRIB_HEAD      (MEM_TOP - 1)  // vlist of items not yet on current page
#define PAGE_HEAD         (MEM_TOP - 2)  // vlist for current page
#define TEMP_HEAD         (MEM_TOP - 3)  // head of a temporary list of some kind
#define HOLD_HEAD         (MEM_TOP - 4)  // head of a temporary list of another kind
#define ADJUST_HEAD       (MEM_TOP - 5)  // head of adjustment list returned by |hpack|
#define ACTIVE            (MEM_TOP - 7)  // head of active list in |line_break|, needs two words
#define ALIGN_HEAD        (MEM_TOP - 8)  // head of preamble list for alignments
#define END_SPAN          (MEM_TOP - 9)  // tail of spanned - width lists
#define OMIT_TEMPLATE     (MEM_TOP - 10) // a constant token list
#define NULL_LIST         (MEM_TOP - 11) // permanently empty list
#define LIG_TRICK         (MEM_TOP - 12) // a ligature masquerading as a |CHAR_NODE|
#define GARBAGE           (MEM_TOP - 12) // used for scrap information
#define BACKUP_HEAD       (MEM_TOP - 13) // head of token list built by |scan_keyword|
#define HI_MEM_STAT_MIN   (MEM_TOP - 13) // smallest statically allocated word in the one-word |mem|
#define HI_MEM_STAT_USAGE 14             // the number of one-word nodes always present
// ~~~ End section 162 ~~~

// ~~~ Section 207 ~~~
#define ESCAPE        0  // escape delimiter (called \ in The TeXbook)
#define RELAX         0  // do nothing (\relax)
#define LEFT_BRACE    1  // beginning of a group ({)
#define RIGHT_BRACE   2  // ending of a group (})
#define MATH_SHIFT    3  // mathematics shift character ($)
#define TAB_MARK      4  // alignment delimiter (&, \span)
#define CAR_RET       5  // end of line (CARRIAGE_RETURN, \cr, \crcr)
#define OUT_PARAM     5  // output a macro parameter
#define MAC_PARAM     6  // macro parameter symbol (#)
#define SUP_MARK      7  // superscript (^)
#define SUB_MARK      8  // subscript (_)
#define IGNORE        9  // characters to ignore (^^@)
#define ENDV          9  // end of <v_j> list in alignment template
#define SPACER        10 // characters equivalent to blank space ( )
#define LETTER        11 // characters regarded as letters (A..Z, a..z})
#define OTHER_CHAR    12 // none of the special character types
#define ACTIVE_CHAR   13 // characters that invoke macros (~)
#define PAR_END       13 // end of paragraph (\par)
#define MATCH         13 // match a macro parameter
#define COMMENT       14 // characters that introduce comments (%)
#define END_MATCH     14 // end of parameters to macro
#define STOP          14 // end of job (\end, \dump)
#define INVALID_CHAR  15 // characters that shouldn't appear (^^?)
#define DELIM_NUM     15 // specify delimiter numerically (\delimiter)
#define MAX_CHAR_CODE 15 // largest catcode for individual characters
// ~~~ End section 207 ~~~

// ~~~ Section 208 ~~~
#define CHAR_NUM                 16 // character specified numerically (\char)
#define MATH_CHAR_NUM            17 // explicit math code (\mathchar)
#define MARK                     18 // mark definition (\mark)
#define XRAY                     19 // peek inside of TeX (\show, \showbox, etc.)
#define MAKE_BOX                 20 // make a box (\box, \copy, \hbox, etc.)
#define HMOVE                    21 // horizontal motion (\moveleft, \moveright)
#define VMOVE                    22 // vertical motion (\raise, \lower)
#define UN_HBOX                  23 // unglue a box (\unhbox, \unhcopy)
#define UN_VBOX                  24 // unglue a box (\unvbox, \unvcopy)
#define REMOVE_ITEM              25 // nullify last item (\unpenalty, \unkern, \unskip)
#define HSKIP                    26 // horizontal glue (\hskip, \hfil, etc.)
#define VSKIP                    27 // vertical glue (\vskip, \vfil, etc.)
#define MSKIP                    28 // math glue (\mskip)
#define KERN                     29 // fixed space (\kern)
#define MKERN                    30 // math kern (\mkern)
#define LEADER_SHIP              31 // use a box (\shipout, \leaders, etc.)
#define HALIGN                   32 // horizontal table alignment (\halign)
#define VALIGN                   33 // vertical table alignment (\valign)
#define NO_ALIGN                 34 // temporary escape from alignment (\noalign)
#define VRULE                    35 // vertical rule (\vrule)
#define HRULE                    36 // horizontal rule (\hrule)
#define INSERT                   37 // vlist inserted in box (\insert)
#define VADJUST                  38 // vlist inserted in enclosing paragraph (\vadjust)
#define IGNORE_SPACES            39 // gobble |spacer| tokens (\ignorespaces)
#define AFTER_ASSIGNMENT         40 // save till assignment is done (\afterassignment)
#define AFTER_GROUP              41 // save till group is done (\aftergroup)
#define BREAK_PENALTY            42 // additional badness (\penalty)
#define START_PAR                43 // begin paragraph (\indent, \noindent)
#define ITAL_CORR                44 // italic correction (\/)
#define ACCENT                   45 // attach accent in text (\accent)
#define MATH_ACCENT              46 // attach accent in math (\mathaccent)
#define DISCRETIONARY            47 // discretionary texts (\-, \discretionary)
#define EQ_NO                    48 // equation number (\eqno, \leqno)
#define LEFT_RIGHT               49 // variable delimiter (\left, \right)
#define MATH_COMP                50 // component of formula (\mathbin, etc.)
#define LIMIT_SWITCH             51 // diddle limit conventions (\displaylimits, etc.)
#define ABOVE                    52 // generalized fraction (\above, \atop, etc.)
#define MATH_STYLE               53 // style specification (\displaystyle, etc.)
#define MATH_CHOICE              54 // choice specification (\mathchoice)
#define NON_SCRIPT               55 // conditional math glue (\nonscript)
#define VCENTER                  56 // vertically center a vbox (\vcenter)
#define CASE_SHIFT               57 // force specific case (\lowercase, \uppercase)
#define MESSAGE                  58 // send to user (\message, \errmessage)
#define EXTENSION                59 // extensions to \TeX\ (\write, \special, etc.)
#define IN_STREAM                60 // files for reading (\openin, \closein)
#define BEGIN_GROUP              61 // begin local grouping (\begingroup)
#define END_GROUP                62 // end local grouping (\endgroup)
#define OMIT                     63 // omit alignment template (\omit)
#define EX_SPACE                 64 // explicit space (\ )
#define NO_BOUNDARY              65 // suppress boundary ligatures (\noboundary)
#define RADICAL                  66 // square root and similar signs (\radical)
#define END_CS_NAME              67 // end control sequence (\endcsname)
#define MIN_INTERNAL             68 // the smallest code that can follow \the
#define CHAR_GIVEN               68 // character code defined by \chardef
#define MATH_GIVEN               69 // math code defined by \mathchardef
#define LAST_ITEM                70 // most recent item (\lastpenalty, \lastkern, \lastskip)
#define MAX_NON_PREFIXED_COMMAND 70 // largest command code that can't be \global
// ~~~ End section 208 ~~~

// ~~~ Section 209 ~~~
#define TOKS_REGISTER     71  // token list register (\toks)
#define ASSIGN_TOKS       72  // special token list (\output, \everypar, etc.)
#define ASSIGN_INT        73  // user-defined integer (\tolerance, \day, etc.)
#define ASSIGN_DIMEN      74  // user-defined length (\hsize, etc.)
#define ASSIGN_GLUE       75  // user-defined glue (\baselineskip, etc.)
#define ASSIGN_MU_GLUE    76  // user-defined muglue (\thinmuskip, etc.)
#define ASSIGN_FONT_DIMEN 77  // user-defined font dimension (\fontdimen)
#define ASSIGN_FONT_INT   78  // user-defined font integer (\hyphenchar, \skewchar)
#define SET_AUX           79  // specify state info (\spacefactor, \prevdepth)
#define SET_PREV_GRAF     80  // specify state info (\prevgraf)
#define SET_PAGE_DIMEN    81  // specify state info (\pagegoal, etc.)
#define SET_PAGE_INT      82  // specify state info (\deadcycles, \insertpenalties)
#define SET_BOX_DIMEN     83  // change dimension of box (\wd, \ht, \dp)
#define SET_SHAPE         84  // specify fancy paragraph shape (\parshape)
#define DEF_CODE          85  // define a character code (\catcode, etc.)
#define DEF_FAMILY        86  // declare math fonts (\textfont, etc.)
#define SET_FONT          87  // set current font (font identifiers)
#define DEF_FONT          88  // define a font file (\font)
#define REGISTER          89  // internal register (\count, \dimen, etc.)
#define MAX_INTERNAL      89  // the largest code that can follow \the
#define ADVANCE           90  // advance a register or parameter (\advance)
#define MULTIPLY          91  // multiply a register or parameter (\multiply)
#define DIVIDE            92  // divide a register or parameter (\divide)
#define PREFIX            93  // qualify a definition (\global, \long, \outer)
#define LET               94  // assign a command code (\let, \futurelet)
#define SHORTHAND_DEF     95  // code definition (\chardef, \countdef, etc.)
#define READ_TO_CS        96  // read into a control sequence (\read)
#define DEF               97  // macro definition (\def, \gdef, \xdef, \edef)
#define SET_BOX           98  // set a box (\setbox)
#define HYPH_DATA         99  // hyphenation data (\hyphenation, \patterns)
#define SET_INTERACTION   100 // define level of interaction (\batchmode, etc.)
#define MAX_COMMAND       100 // the largest command code seen at |big_switch|
// ~~~ End section 209 ~~~

// ~~~ Section 210 ~~~
#define UNDEFINED_CS    (MAX_COMMAND + 1)  // initial state of most |eq_type| fields
#define EXPAND_AFTER    (MAX_COMMAND + 2)  // special expansion (\expandafter)
#define NO_EXPAND       (MAX_COMMAND + 3)  // special nonexpansion (\noexpand)
#define INPUT           (MAX_COMMAND + 4)  // input a source file (\input, \endinput)
#define IF_TEST         (MAX_COMMAND + 5)  // conditional text (\if, \ifcase, etc.)
#define FI_OR_ELSE      (MAX_COMMAND + 6)  // delimiters for conditionals (\else, etc.)
#define CS_NAME         (MAX_COMMAND + 7)  // make a control sequence from tokens (\csname)
#define CONVERT         (MAX_COMMAND + 8)  // convert to text (\number, \string, etc.)
#define THE             (MAX_COMMAND + 9)  // expand an internal quantity (\the)
#define TOP_BOT_MARK    (MAX_COMMAND + 10) // inserted mark (\topmark, etc.)
#define CALL            (MAX_COMMAND + 11) // non-long, non-outer control sequence
#define LONG_CALL       (MAX_COMMAND + 12) // long, non-outer control sequence
#define OUTER_CALL      (MAX_COMMAND + 13) // non-long, outer control sequence
#define LONG_OUTER_CALL (MAX_COMMAND + 14) // long, outer control sequence
#define END_TEMPLATE    (MAX_COMMAND + 15) // end of an alignment template
#define DONT_EXPAND     (MAX_COMMAND + 16) // the following token was marked by \noexpand
#define GLUE_REF        (MAX_COMMAND + 17) // the equivalent points to a glue specification
#define SHAPE_REF       (MAX_COMMAND + 18) // the equivalent points to a parshape specification
#define BOX_REF         (MAX_COMMAND + 19) // the equivalent points to a box node, or is |null|
#define DATA            (MAX_COMMAND + 20) // the equivalent is simply a halfword number
// ~~~ End section 210 ~~~

// ~~~ Section 211 ~~~
#define VMODE 1                         // vertical mode
#define HMODE (VMODE + MAX_COMMAND + 1) // horizontal mode
#define MMODE (HMODE + MAX_COMMAND + 1) // math mode
// ~~~ End section 211 ~~~

// ~~~ Section 212 ~~~
#define IGNORE_DEPTH -65536000 // |prev_depth| value is ignored
// ~~~ End section 212 ~~~

// ~~~ Section 221 ~~~
#define LEVEL_ZERO MIN_QUARTERWORD // level for undefined quantities
#define LEVEL_ONE (LEVEL_ZERO + 1) // outermost level for defined quantities
// ~~~ End section 221 ~~~

// ~~~ Section 222 ~~~
#define ACTIVE_BASE                1                                // beginning of region 1, for active character equivalents
#define SINGLE_BASE                (ACTIVE_BASE + 256)              // equivalents of one-character control sequences
#define NULL_CS                    (SINGLE_BASE + 256)              // equivalent of \csname\endcsname
#define HASH_BASE                  (NULL_CS + 1)                    // beginning of region 2, for the hash table
#define FROZEN_CONTROL_SEQUENCE    (HASH_BASE + HASH_SIZE)          // for error recovery
#define FROZEN_PROTECTION          FROZEN_CONTROL_SEQUENCE          // inaccessible but definable
#define FROZEN_CR                  (FROZEN_CONTROL_SEQUENCE + 1)    // permanent `\cr'
#define FROZEN_END_GROUP           (FROZEN_CONTROL_SEQUENCE + 2)    // permanent `\endgroup'
#define FROZEN_RIGHT               (FROZEN_CONTROL_SEQUENCE + 3)    // permanent `\right'
#define FROZEN_FI                  (FROZEN_CONTROL_SEQUENCE + 4)    // permanent `\fi'
#define FROZEN_END_TEMPLATE        (FROZEN_CONTROL_SEQUENCE + 5)    // permanent `\endtemplate'
#define FROZEN_ENDV                (FROZEN_CONTROL_SEQUENCE + 6)    // second permanent `\endtemplate'
#define FROZEN_RELAX               (FROZEN_CONTROL_SEQUENCE + 7)    // permanent `\relax'
#define END_WRITE                  (FROZEN_CONTROL_SEQUENCE + 8)    // permanent `\endwrite'
#define FROZEN_DONT_EXPAND         (FROZEN_CONTROL_SEQUENCE + 9)    // permanent `\notexpanded:'
#define FROZEN_NULL_FONT           (FROZEN_CONTROL_SEQUENCE + 10)   // permanent `\nullfont'
#define FONT_ID_BASE               (FROZEN_NULL_FONT - FONT_BASE)   // begins table of 257 permanent font identifiers
#define UNDEFINED_CONTROL_SEQUENCE (FROZEN_NULL_FONT + 257)         // dummy location
#define GLUE_BASE                  (UNDEFINED_CONTROL_SEQUENCE + 1) // beginning of region 3
// ~~~ End section 222 ~~~

// ~~~ Section 224 ~~~
#define LINE_SKIP_CODE                0      // interline glue if |baseline_skip| is infeasible
#define BASELINE_SKIP_CODE            1      // desired glue between baselines
#define PAR_SKIP_CODE                 2      // extra glue just above a paragraph
#define ABOVE_DISPLAY_SKIP_CODE       3      // extra glue just above displayed math
#define BELOW_DISPLAY_SKIP_CODE       4      // extra glue just below displayed math
#define ABOVE_DISPLAY_SHORT_SKIP_CODE 5      // glue above displayed math following short lines
#define BELOW_DISPLAY_SHORT_SKIP_CODE 6      // glue below displayed math following short lines
#define LEFT_SKIP_CODE                7      // glue at left of justified lines
#define RIGHT_SKIP_CODE               8      // glue at right of justified lines
#define TOP_SKIP_CODE                 9      // glue at top of main pages
#define SPLIT_TOP_SKIP_CODE           10     // glue at top of split pages
#define TAB_SKIP_CODE                 11     // glue between aligned entries
#define SPACE_SKIP_CODE               12     // glue between words (if not |ZERO_GLUE|)
#define XSPACE_SKIP_CODE              13     // glue after sentences (if not |ZERO_GLUE|)
#define PAR_FILL_SKIP_CODE            14     // glue on last line of paragraph
#define THIN_MU_SKIP_CODE             15     // thin space in math formula
#define MED_MU_SKIP_CODE              16     // medium space in math formula
#define THICK_MU_SKIP_CODE            17     // thick space in math formula
#define GLUE_PARS                     18     // total number of glue parameters
#define SKIP_BASE    (GLUE_BASE + GLUE_PARS) // table of 256 "skip" registers
#define MU_SKIP_BASE (SKIP_BASE + 256)       // table of 256 "muskip" registers
#define LOCAL_BASE   (MU_SKIP_BASE + 256)    // beginning of region 4
// ~~~ End section 224 ~~~

// ~~~ Section 230 ~~~
#define PAR_SHAPE_LOC      LOCAL_BASE             // specifies paragraph shape
#define OUTPUT_ROUTINE_LOC (LOCAL_BASE + 1)       // points to token list for \output
#define EVERY_PAR_LOC      (LOCAL_BASE + 2)       // points to token list for \everypar
#define EVERY_MATH_LOC     (LOCAL_BASE + 3)       // points to token list for \everymath
#define EVERY_DISPLAY_LOC  (LOCAL_BASE + 4)       // points to token list for \everydisplay
#define EVERY_HBOX_LOC     (LOCAL_BASE + 5)       // points to token list for \everyhbox
#define EVERY_VBOX_LOC     (LOCAL_BASE + 6)       // points to token list for \everyvbox
#define EVERY_JOB_LOC      (LOCAL_BASE + 7)       // points to token list for \everyjob
#define EVERY_CR_LOC       (LOCAL_BASE + 8)       // points to token list for \everycr
#define ERR_HELP_LOC       (LOCAL_BASE + 9)       // points to token list for \errhelp
#define TOKS_BASE          (LOCAL_BASE + 10)      // table of 256 token list registers
#define BOX_BASE           (TOKS_BASE + 256)      // table of 256 box registers
#define CUR_FONT_LOC       (BOX_BASE + 256)       // internal font number outside math mode
#define MATH_FONT_BASE     (CUR_FONT_LOC + 1)     // table of 48 math font numbers
#define CAT_CODE_BASE      (MATH_FONT_BASE + 48)  // table of 256 command codes (the "catcodes")
#define LC_CODE_BASE       (CAT_CODE_BASE + 256)  // table of 256 lowercase mappings
#define UC_CODE_BASE       (LC_CODE_BASE + 256)   // table of 256 uppercase mappings
#define SF_CODE_BASE       (UC_CODE_BASE + 256)   // table of 256 spacefactor mappings
#define MATH_CODE_BASE     (SF_CODE_BASE + 256)   // table of 256 math mode mappings
#define INT_BASE           (MATH_CODE_BASE + 256) // beginning of region 5
// ~~~ End section 230 ~~~

// ~~~ Section 232 ~~~
#define NULL_FONT FONT_BASE
#define VAR_CODE 0x7000 // math code meaning "use the current family"
// ~~~ End section 232 ~~~

// ~~~ Section 236 ~~~
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
// ~~~ End section 236 ~~~

// ~~~ Section 247 ~~~
#define PAR_INDENT_CODE           0           // indentation of paragraphs
#define MATH_SURROUND_CODE        1           // space around math in text
#define LINE_SKIP_LIMIT_CODE      2           // threshold for |line_skip| instead of |baseline_skip|
#define HSIZE_CODE                3           // line width in horizontal mode
#define VSIZE_CODE                4           // page height in vertical mode
#define MAX_DEPTH_CODE            5           // maximum depth of boxes on main pages
#define SPLIT_MAX_DEPTH_CODE      6           // maximum depth of boxes on split pages
#define BOX_MAX_DEPTH_CODE        7           // maximum depth of explicit vboxes
#define HFUZZ_CODE                8           // tolerance for overfull hbox messages
#define VFUZZ_CODE                9           // tolerance for overfull vbox messages
#define DELIMITER_SHORTFALL_CODE  10          // maximum amount uncovered by variable delimiters
#define NULL_DELIMITER_SPACE_CODE 11          // blank space in null delimiters
#define SCRIPT_SPACE_CODE         12          // extra space after subscript or superscript
#define PRE_DISPLAY_SIZE_CODE     13          // length of text preceding a display
#define DISPLAY_WIDTH_CODE        14          // length of line for displayed equation
#define DISPLAY_INDENT_CODE       15          // indentation of line for displayed equation
#define OVERFULL_RULE_CODE        16          // width of rule that identifies overfull hboxes
#define HANG_INDENT_CODE          17          // amount of hanging indentation
#define H_OFFSET_CODE             18          // amount of horizontal offset when shipping pages out
#define V_OFFSET_CODE             19          // amount of vertical offset when shipping pages out
#define EMERGENCY_STRETCH_CODE    20          // reduces badnesses on final pass of line-breaking
#define DIMEN_PARS                21          // total number of dimension parameters
#define SCALED_BASE (DIMEN_BASE + DIMEN_PARS) // table of 256 user-defined \dimen registers
#define EQTB_SIZE   (SCALED_BASE + 255)       // largest subscript of |eqtb|
// ~~~ End section 247 ~~~

// ~~~ Section 268 ~~~
#define RESTORE_OLD_VALUE 0 // |save_type| when a value should be restored later
#define RESTORE_ZERO      1 // |save_type| when an undefined entry should be restored
#define INSERT_TOKEN      2 // |save_type| when a token is being saved for later use
#define LEVEL_BOUNDARY    3 // |save_type| corresponding to beginning of group
// ~~~ End section 268 ~~~

// ~~~ Section 269 ~~~
#define BOTTOM_LEVEL        0    // group code for the outside world
#define SIMPLE_GROUP        1    // group code for local structure only
#define HBOX_GROUP          2    // code for '\hbox{...}'
#define ADJUSTED_HBOX_GROUP 3    // code for '\hbox{...}' in vertical mode
#define VBOX_GROUP          4    // code for '\vbox{...}'
#define VTOP_GROUP          5    // code for '\vtop{...}'
#define ALIGN_GROUP         6    // code for '\halign{...}', '\valign{...}'
#define NO_ALIGN_GROUP      7    // code for '\noalign{...}'
#define OUTPUT_GROUP        8    // code for output routine
#define MATH_GROUP          9    // code for, e.g., `^{...}'
#define DISC_GROUP          10   // code for '\discretionary{...}{...}{...}'
#define INSERT_GROUP        11   // code for '\insert{...}', '\vadjust{...}'
#define VCENTER_GROUP       12   // code for '\vcenter{...}'
#define MATH_CHOICE_GROUP   13   // code for '\mathchoice{...}{...}{...}{...}'
#define SEMI_SIMPLE_GROUP   14   // code for '\begingroup...\endgroup'
#define MATH_SHIFT_GROUP    15   // code for '$...$'
#define MATH_LEFT_GROUP     16   // code for '\left...\right'
#define MAX_GROUP_CODE      16
// ~~~ End section 269 ~~~

// ~~~ Section 289 ~~~
#define CS_TOKEN_FLAG      0xfff  // amount added to the |eqtb| location in a token that stands for a control sequence; is a multiple of 256, less 1
#define LEFT_BRACE_TOKEN   0x100  // 2^8 * |LEFT_BRACE|
#define LEFT_BRACE_LIMIT   0x200  // 2^8 * (|LEFT_BRACE| + 1)
#define RIGHT_BRACE_TOKEN  0x200  // 2^8 * |RIGHT_BRACE|
#define RIGHT_BRACE_LIMIT  0x300  // 2^8 * (|RIGHT_BRACE| + 1)
#define MATH_SHIFT_TOKEN   0x300  // 2^8 * |MATH_SHIFT|
#define TAB_TOKEN          0x400  // 2^8 * |TAB_MARK|
#define OUT_PARAM_TOKEN    0x500  // 2^8 * |OUT_PARAM|
#define SPACE_TOKEN        0xa20  // 2^8 * |SPACER| + |' '|
#define LETTER_TOKEN       0xb00  // 2^8 * |LETTER|
#define OTHER_TOKEN        0xc00  // 2^8 * |OTHER_CHAR|
#define MATCH_TOKEN        0xd00  // 2^8 * |MATCH|
#define END_MATCH_TOKEN    0xe00  // 2^8 * |END_MATCH|
// ~~~ End section 289 ~~~

// ~~~ Section 303 ~~~
#define MID_LINE    1                                   // |state| code when scanning a line of characters
#define SKIP_BLANKS (2 + MAX_CHAR_CODE)                 // |state| code when ignoring blanks
#define NEW_LINE    (3 + MAX_CHAR_CODE + MAX_CHAR_CODE) // |state| code at start of line
// ~~~ End section 303 ~~~

// ~~~ Section 305 ~~~
#define SKIPPING  1 // |scanner_status| when passing conditional text
#define DEFINING  2 // |scanner_status| when reading a macro definition
#define MATCHING  3 // |scanner_status| when reading macro arguments
#define ALIGNING  4 // |scanner_status| when reading an alignment preamble
#define ABSORBING 5 // |scanner_status| when reading a balanced text
// ~~~ End section 305 ~~~

// ~~~ Section 307 ~~~
#define TOKEN_LIST         0  // |state| code when scanning a token list
#define PARAMETER          0  // |token_type| code for parameter
#define U_TEMPLATE         1  // |token_type| code for <u_j> template
#define V_TEMPLATE         2  // |token_type| code for <v_j> template
#define BACKED_UP          3  // |token_type| code for text to be reread
#define INSERTED           4  // |token_type| code for inserted texts
#define MACRO              5  // |token_type| code for defined control sequences
#define OUTPUT_TEXT        6  // |token_type| code for output routines
#define EVERY_PAR_TEXT     7  // |token_type| code for \everypar
#define EVERY_MATH_TEXT    8  // |token_type| code for \everymath
#define EVERY_DISPLAY_TEXT 9  // |token_type| code for \everydisplay
#define EVERY_HBOX_TEXT    10 // |token_type| code for \everyhbox
#define EVERY_VBOX_TEXT    11 // |token_type| code for \everyvbox
#define EVERY_JOB_TEXT     12 // |token_type| code for \everyjob
#define EVERY_CR_TEXT      13 // |token_type| code for \everycr
#define MARK_TEXT          14 // |token_type| code for \topmark, etc.
#define WRITE_TEXT         15 // |token_type| code for \write
// ~~~ End section 307 ~~~

// ~~~ Section 358 ~~~
#define NO_EXPAND_FLAG 257 // this characterizes a special variant of |RELAX|
// ~~~ End section 358 ~~~

// ~~~ Section 382 ~~~
#define TOP_MARK_CODE         0 // the mark in effect at the previous page break
#define FIRST_MARK_CODE       1 // the first mark between |top_mark| and |bot_mark|
#define BOT_MARK_CODE         2 // the mark in effect at the current page break
#define SPLIT_FIRST_MARK_CODE 3 // the first mark found by \vsplit
#define SPLIT_BOT_MARK_CODE   4 // the last mark found by \vsplit
// ~~~ End section 382 ~~~

// ~~~ Section 410 ~~~
#define INT_VAL   0 // integer values
#define DIMEN_VAL 1 // dimension values
#define GLUE_VAL  2 // glue specifications
#define MU_VAL    3 // math glue specifications
#define IDENT_VAL 4 // font identifier
#define TOK_VAL   5 // token lists
// ~~~ End section 410 ~~~

// ~~~ Section 416 ~~~
#define INPUT_LINE_NO_CODE (GLUE_VAL + 1) // code for \inputlineno
#define BADNESS_CODE       (GLUE_VAL + 2) // code for \badness
// ~~~ End section 416 ~~~

// ~~~ Section 421 ~~~
#define MAX_DIMEN 0x3fffffff // 2^{30} - 1
// ~~~ End section 421 ~~~

// ~~~ Section 438 ~~~
#define OCTAL_TOKEN             (OTHER_TOKEN + '\'') // apostrophe, indicates an octal constant
#define HEX_TOKEN               (OTHER_TOKEN + '"')  // double quote, indicates a hex constant
#define ALPHA_TOKEN             (OTHER_TOKEN + '`')  // reverse apostrophe, precedes alpha constants
#define POINT_TOKEN             (OTHER_TOKEN + '.')  // decimal point
#define CONTINENTAL_POINT_TOKEN (OTHER_TOKEN + ',')  // decimal point, Eurostyle
// ~~~ End section 438 ~~~

// ~~~ Section 445 ~~~
#define INFINITY_     0x7fffffff           // the largest positive value that TeX knows
#define ZERO_TOKEN    (OTHER_TOKEN + '0')  // zero, the smallest digit
#define A_TOKEN       (LETTER_TOKEN + 'A') // the smallest special hex digit
#define OTHER_A_TOKEN (OTHER_TOKEN + 'A')  // special hex digit of type |OTHER_CHAR|
// ~~~ End section 445 ~~~

// ~~~ Section 463 ~~~
#define DEFAULT_RULE 26214 // 0.4 pt
// ~~~ End section 463 ~~~

// ~~~ Section 468 ~~~
#define NUMBER_CODE        0 // command code for \number
#define ROMAN_NUMERAL_CODE 1 // command code for \romannumeral
#define STRING_CODE        2 // command code for \string
#define MEANING_CODE       3 // command code for \meaning
#define FONT_NAME_CODE     4 // command code for \fontname
#define JOB_NAME_CODE      5 // command code for \jobname
// ~~~ End section 468 ~~~

// ~~~ Section 480 ~~~
#define CLOSED    2 // not open, or at end of file
#define JUST_OPEN 1 // newly opened, first line not yet read
// ~~~ End section 480 ~~~

// ~~~ Section 487 ~~~
#define IF_CHAR_CODE  0   // '\if' 
#define IF_CAT_CODE   1   // '\ifcat' 
#define IF_INT_CODE   2   // '\ifnum' 
#define IF_DIM_CODE   3   // '\ifdim' 
#define IF_ODD_CODE   4   // '\ifodd' 
#define IF_VMODE_CODE 5   // '\ifvmode' 
#define IF_HMODE_CODE 6   // '\ifhmode' 
#define IF_MMODE_CODE 7   // '\ifmmode' 
#define IF_INNER_CODE 8   // '\ifinner' 
#define IF_VOID_CODE  9   // '\ifvoid' 
#define IF_HBOX_CODE  10  // '\ifhbox' 
#define IF_VBOX_CODE  11  // '\ifvbox' 
#define IFX_CODE      12  // '\ifx' 
#define IF_EOF_CODE   13  // '\ifeof' 
#define IF_TRUE_CODE  14  // '\iftrue' 
#define IF_FALSE_CODE 15  // '\iffalse' 
#define IF_CASE_CODE  16  // '\ifcase' 
// ~~~ End section 487 ~~~

// ~~~ Section 489 ~~~
#define IF_NODE_SIZE 2 // number of words in stack entry for conditionals
#define IF_CODE      1 // code for \if... being evaluated
#define FI_CODE      2 // code for \f
#define ELSE_CODE    3 // code for \else
#define OR_CODE      4 // code for \or
// ~~~ End section 489 ~~~

// ~~~ Section 520 ~~~
#define FORMAT_DEFAULT_LENGTH 20      // length of the |tex_format_default| string
#define FORMAT_AREA_LENGTH    11      // length of its area part
#define FORMAT_EXT_LENGTH     4       // length of its '.fmt' part
#define FORMAT_EXTENSION      FMT_EXT // the extension, as a WEB constant
// ~~~ End section 520 ~~~

// ~~~ Section 544 ~~~
#define NO_TAG   0 // vanilla character
#define LIG_TAG  1 // character has a ligature/kerning program
#define LIST_TAG 2 // character has a successor in a charlist
#define EXT_TAG  3 // character is extensible
// ~~~ End section 544 ~~~

// ~~~ Section 545 ~~~
#define STOP_FLAG 128 // value indicating 'STOP' in a lig/kern program
#define KERN_FLAG 128 // op code for a kern step
// ~~~ End section 545 ~~~

// ~~~ Section 547 ~~~
#define SLANT_CODE         1
#define SPACE_CODE         2
#define SPACE_STRETCH_CODE 3
#define SPACE_SHRINK_CODE  4
#define X_HEIGHT_CODE      5
#define QUAD_CODE          6
#define EXTRA_SPACE_CODE   7
// ~~~ End section 547 ~~~

// ~~~ Section 549 ~~~
#define NON_CHAR    256 // a |halfword| code that can't match a real character
#define NON_ADDRESS 0   // a spurious |bchar_label|
// ~~~ End section 549 ~~~

// ~~~ Section 557 ~~~
#define KERN_BASE_OFFSET 256*(128 + MIN_QUARTERWORD)
// ~~~ End section 557 ~~~

// ~~~ Section 586 ~~~
#define SET_CHAR_0 0   // typeset character 0 and move right
#define SET1       128 // typeset a character and move right
#define SET_RULE   132 // typeset a rule and move right
#define PUT_RULE   137 // typeset a rule
#define NOP        138 // no operation
#define BOP        139 // beginning of page
#define EOP        140 // ending of page
#define PUSH       141 // save the current positions
#define POP        142 // restore previous positions
#define RIGHT1     143 // move right
#define W0         147 // move right by |w|
#define W1         148 // move right and set |w|
#define X0         152 // move right by |x|
#define X1         153 // move right and set |x|
#define DOWN1      157 // move down
#define Y0         161 // move down by |y|
#define Y1         162 // move down and set |y|
#define Z0         166 // move down by |z|
#define Z1         167 // move down and set |z|
#define FNT_NUM_0  171 // set current font to 0
#define FNT1       235 // set current font
#define XXX1       239 // extension to `DVI` primitives
#define XXX4       242 // potentially long extension to `DVI` primitives
#define FNT_DEF1   243 // define the meaning of a font number
#define PRE        247 // preamble
#define POST       248 // postamble beginning
#define POST_POST  249 // postamble ending
// ~~~ End section 586 ~~~

// ~~~ Section 587 ~~~
#define ID_BYTE 2 // identifies the kind of `DVI` files described here
// ~~~ End section 587 ~~~

// ~~~ Section 605 ~~~
#define MOVEMENT_NODE_SIZE 3 // number of words per entry in the down and right stacks
// ~~~ End section 605 ~~~

// ~~~ Section 608 ~~~
#define Y_HERE  1 // |info| when the movement entry points to a |y| command
#define Z_HERE  2 // |info| when the movement entry points to a |z| command
#define YZ_OK   3 // |info| corresponding to an unconstrained |down| command
#define Y_OK    4 // |info| corresponding to a |down| that can't become a |z|
#define Z_OK    5 // |info| corresponding to a |down| that can't become a |y|
#define D_FIXED 6 // |info| corresponding to a |down| that can't change
// ~~~ End section 608 ~~~

// ~~~ Section 611 ~~~
#define NONE_SEEN 0  // no |Y_HERE| or |Z_HERE| nodes have been encountered yet
#define Y_SEEN    6  // we have seen |Y_HERE| but not |Z_HERE|
#define Z_SEEN    12 // we have seen |Z_HERE| but not |Y_HERE|
// ~~~ End section 611 ~~~

// ~~~ Section 625 ~~~
#define BILLION 1000000000.0
// ~~~ End section 625 ~~~

// ~~~ Section 681 ~~~
#define NOAD_SIZE      4 // number of words in a normal noad
#define MATH_CHAR      1 // |math_type| when the attribute is simple
#define SUB_BOX        2 // |math_type| when the attribute is a box
#define SUB_MLIST      3 // |math_type| when the attribute is a formula
#define MATH_TEXT_CHAR 4 // |math_type| when italic correction is dubious
// ~~~ End section 681 ~~~

// ~~~ Section 682 ~~~
#define ORD_NOAD   (UNSET_NODE + 3) // |type| of a noad classified Ord
#define OP_NOAD    (ORD_NOAD + 1)   // |type| of a noad classified Op
#define BIN_NOAD   (ORD_NOAD + 2)   // |type| of a noad classified Bin
#define REL_NOAD   (ORD_NOAD + 3)   // |type| of a noad classified Rel
#define OPEN_NOAD  (ORD_NOAD + 4)   // |type| of a noad classified Open
#define CLOSE_NOAD (ORD_NOAD + 5)   // |type| of a noad classified Close
#define PUNCT_NOAD (ORD_NOAD + 6)   // |type| of a noad classified Punct
#define INNER_NOAD (ORD_NOAD + 7)   // |type| of a noad classified Inner
#define LIMITS     1                // |subtype| of |OP_NOAD| whose scripts are to be above, below
#define NO_LIMITS  2                // |subtype| of |OP_NOAD| whose scripts are to be normal
// ~~~ End section 682 ~~~

// ~~~ Section 683 ~~~
#define RADICAL_NOAD       (INNER_NOAD + 1)   // |type| of a noad for square roots
#define RADICAL_NOAD_SIZE  5                  // number of |mem| words in a radical noad
#define FRACTION_NOAD      (RADICAL_NOAD + 1) // |type| of a noad for generalized fractions
#define FRACTION_NOAD_SIZE 6                  // number of |mem| words in a fraction noad
#define DEFAULT_CODE       0x40000000         // denotes |default_rule_thickness|
// ~~~ End section 683 ~~~

// ~~~ Section 687 ~~~
#define UNDER_NOAD       (FRACTION_NOAD + 1) // |type| of a noad for underlining
#define OVER_NOAD        (UNDER_NOAD + 1)    // |type| of a noad for overlining
#define ACCENT_NOAD      (OVER_NOAD + 1)     // |type| of a noad for accented subformulas
#define ACCENT_NOAD_SIZE 5                   // number of |mem| words in an accent noad
#define VCENTER_NOAD     (ACCENT_NOAD + 1)   // |type| of a noad for \vcenter
#define LEFT_NOAD        (VCENTER_NOAD + 1)  // |type| of a noad for \left
#define RIGHT_NOAD       (LEFT_NOAD + 1)     // |type| of a noad for \right
// ~~~ End section 687 ~~~

// ~~~ Section 688 ~~~
#define STYLE_NODE          (UNSET_NODE + 1) // |type| of a style node
#define STYLE_NODE_SIZE     3                // number of words in a style node
#define DISPLAY_STYLE       0                // |subtype| for \displaystyle
#define TEXT_STYLE          2                // |subtype| for \textstyle
#define SCRIPT_STYLE        4                // |subtype| for \scriptstyle
#define SCRIPT_SCRIPT_STYLE 6                // |subtype| for \scriptscriptstyle
#define CRAMPED             1                // add this to an uncramped style if you want to cramp it
// ~~~ End section 688 ~~~

// ~~~ Section 689 ~~~
#define CHOICE_NODE (UNSET_NODE + 2) // |type| of a choice node
// ~~~ End section 689 ~~~

// ~~~ Section 699 ~~~
#define TEXT_SIZE          0  // size code for the largest size in a family
#define SCRIPT_SIZE        16 // size code for the medium size in a family
#define SCRIPT_SCRIPT_SIZE 32 // size code for the smallest size in a family
// ~~~ End section 699 ~~~

// ~~~ Section 700 ~~~
#define TOTAL_MATHSY_PARAMS 22
// ~~~ End section 700 ~~~

// ~~~ Section 701 ~~~
#define TOTAL_MATHEX_PARAMS 13
// ~~~ End section 701 ~~~

// ~~~ Section 770 ~~~
#define ALIGN_STACK_NODE_SIZE 5 // number of |mem| words to save alignment states
// ~~~ End section 770 ~~~

// ~~~ Section 780 ~~~
#define SPAN_CODE          256           // distinct from any character
#define CR_CODE            257           // distinct from |SPAN_CODE| and from any character
#define CR_CR_CODE         (CR_CODE + 1) // this distinguishes \crcr from \cr
#define END_TEMPLATE_TOKEN (CS_TOKEN_FLAG + FROZEN_END_TEMPLATE)
// ~~~ End section 780 ~~~

// ~~~ Section 797 ~~~
#define SPAN_NODE_SIZE 2 // number of |mem| words for a span node
// ~~~ End section 797 ~~~

// ~~~ Section 817 ~~~
#define TIGHT_FIT      3 // fitness classification for lines shrinking 0.5 to 1.0 of their shrinkability
#define LOOSE_FIT      1 // fitness classification for lines stretching 0.5 to 1.0 of their stretchability
#define VERY_LOOSE_FIT 0 // fitness classification for lines stretching more than their stretchability
#define DECENT_FIT     2 // fitness classification for all other lines
// ~~~ End section 817 ~~~

// ~~~ Section 819 ~~~
#define ACTIVE_NODE_SIZE 3      // number of words in active nodes
#define UNHYPHENATED     0      // the |type| of a normal active break node
#define HYPHENATED       1      // the |type| of an active node that breaks at a |DISC_NODE|
#define LAST_ACTIVE      ACTIVE // the active list ends where it begins
// ~~~ End section 819 ~~~

// ~~~ Section 821 ~~~
#define PASSIVE_NODE_SIZE 2 // number of words in passive nodes
// ~~~ End section 821 ~~~

// ~~~ Section 822 ~~~
#define DELTA_NODE_SIZE 7 // number of words in a delta node
#define DELTA_NODE      2 // |type| field in a delta node
// ~~~ End section 822 ~~~

// ~~~ Section 833 ~~~
#define AWFUL_BAD 0x3fffffff // more than a billion demerits
// ~~~ End section 833 ~~~

// ~~~ Section 974 ~~~
#define DEPLORABLE 100000 // more than |INF_BAD|, but less than |AWFUL_BAD|
// ~~~ End section 974 ~~~

// ~~~ Section 980 ~~~
#define INSERTS_ONLY 1 // |page_contents| when an insert node has been contributed, but no boxes
#define BOX_THERE    2 // |page_contents| when a box or rule has been contributed
// ~~~ End section 980 ~~~

// ~~~ Section 981 ~~~
#define PAGE_INS_NODE_SIZE 4 // number of words for a page insertion node
#define INSERTING          0 // an insertion class that has not yet overflowed
#define SPLIT_UP           1 // an overflowed insertion class
// ~~~ End section 981 ~~~

// ~~~ Section 1058 ~~~
#define FIL_CODE     0 // identifies \hfil and \vfil
#define FILL_CODE    1 // identifies \hfill and \vfill
#define SS_CODE      2 // identifies \hss and \vss
#define FIL_NEG_CODE 3 // identifies \hfilneg and \vfilneg
#define SKIP_CODE    4 // identifies \hskip and \vskip
#define MSKIP_CODE   5 // identifies \mskip
// ~~~ End section 1058 ~~~

// ~~~ Section 1071 ~~~
#define BOX_FLAG      0x40000000       // context code for '\setbox0'
#define SHIP_OUT_FLAG (BOX_FLAG + 512) // context code for '\shipout'
#define LEADER_FLAG   (BOX_FLAG + 513) // context code for '\leaders'
#define BOX_CODE      0                // |chr_code| for '\box'
#define COPY_CODE     1                // |chr_code| for '\copy'
#define LAST_BOX_CODE 2                // |chr_code| for '\lastbox'
#define VSPLIT_CODE   3                // |chr_code| for '\vsplit'
#define VTOP_CODE     4                // |chr_code| for '\vtop'
// ~~~ End section 1071 ~~~

// ~~~ Section 1178 ~~~
#define ABOVE_CODE     0 // '\above' 
#define OVER_CODE      1 // '\over' 
#define ATOP_CODE      2 // '\atop' 
#define DELIMITED_CODE 3 // '\abovewithdelims', etc.
// ~~~ End section 1178 ~~~

// ~~~ Section 1222 ~~~
#define CHAR_DEF_CODE      0 // |shorthand_def| for \chardef
#define MATH_CHAR_DEF_CODE 1 // |shorthand_def| for \mathchardef
#define COUNT_DEF_CODE     2 // |shorthand_def| for \countdef
#define DIMEN_DEF_CODE     3 // |shorthand_def| for \dimendef
#define SKIP_DEF_CODE      4 // |shorthand_def| for \skipdef
#define MU_SKIP_DEF_CODE   5 // |shorthand_def| for \muskipdef
#define TOKS_DEF_CODE      6 // |shorthand_def| for \toksdef
// ~~~ End section 1222 ~~~

// ~~~ Section 1291 ~~~
#define SHOW_CODE       0 // \show 
#define SHOW_BOX_CODE   1 // \showbox 
#define SHOW_THE_CODE   2 // \showthe 
#define SHOW_LISTS_CODE 3 // \showlists 
// ~~~ End section 1291 ~~~

// ~~~ Section 1341 ~~~
#define WRITE_NODE_SIZE 2 // number of words in a write/whatsit node
#define OPEN_NODE_SIZE  3 // number of words in an open/whatsit node
#define OPEN_NODE       0 // |subtype| in whatsits that represent files to \openout
#define WRITE_NODE      1 // |subtype| in whatsits that represent things to \write
#define CLOSE_NODE      2 // |subtype| in whatsits that represent streams to \closeout
#define SPECIAL_NODE    3 // |subtype| in whatsits that represent \special things
#define LANGUAGE_NODE   4 // |subtype| in whatsits that change the current language
// ~~~ End section 1341 ~~~

// ~~~ Section 1344 ~~~
#define IMMEDIATE_CODE    4 // command modifier for \immediate
#define SET_LANGUAGE_CODE 5 // command modifier for \setlanguage
// ~~~ End section 1344 ~~~

// ~~~ Section 1371 ~~~
#define END_WRITE_TOKEN (CS_TOKEN_FLAG + END_WRITE)
// ~~~ End section 1371 ~~~

// ~~~ Section 1381 ~~~
#endif
// ~~~ End section 1381 ~~~
