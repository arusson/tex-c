// ~~~ Section 4 ~~~
// ~~~ Start file |global.c|, 1382 ~~~
#include "tex.h"
// ~~~ End section 1382 ~~~

// ~~~ Global variables, 13 ~~~
int bad; // is some "constant" wrong?

// ~~~ Section 26 ~~~
char name_of_file[FILE_NAME_SIZE + 1]; // extra byte for null byte
int name_length; // this many characters are actually relevant in |name_of_file| (the rest are blank)
// ~~~ End section 26 ~~~

// ~~~ Section 30 ~~~
ASCII_code buffer[BUF_SIZE + 1]; // lines of character being read
int first;                       // the first unused position in |buffer|
int last;                        // end of the line just input to |buffer|
int max_buf_stack;               // largest index used in |buffer|
// ~~~ End section 30 ~~~

// ~~~ Section 39 ~~~
ASCII_code   str_pool[POOL_SIZE + 1];    // the characters
pool_pointer str_start[MAX_STRINGS + 1]; // the starting pointers
pool_pointer pool_ptr;                   // first unused position in |str_pool|
str_number   str_ptr;                    // number of the current string being created
pool_pointer init_pool_ptr;              // the starting value of |pool_ptr|
str_number   init_str_ptr;               // the starting value of |str_ptr|
// ~~~ End section 39 ~~~

// ~~~ Section 54 ~~~
alpha_file log_file;                  // transcript of TeX session
int selector;                         // where to print a message
unsigned char dig[23];                // digits in a number being output
int tally;                            // the number of characters recently printed
int term_offset;                      // the number of characters on the current terminal line
int file_offset;                      // the number of characters on the current file line
ASCII_code trick_buf[ERROR_LINE + 1]; // circular buffer for pseudoprinting
int trick_count;                      // threshold for pseudoprinting, explained later
int first_count;                      // another variable for pseudoprinting
// ~~~ End section 54 ~~~

// ~~~ Section 73 ~~~
int interaction; // current level of interaction
// ~~~ End section 73 ~~~

// ~~~ Section 76 ~~~
bool deletions_allowed; // is it safe for |error| to call |get_token|?
bool set_box_allowed;   // is it safe to do a \setbox assignment?
int history;            // has the source input been clean so far?
int error_count;        // the number of scrolled errors since the last paragraph ended
// ~~~ End section 76 ~~~

// ~~~ Section 79 ~~~
char *help_line[6]; // helps for the next |error|
int help_ptr;       // the number of help lines present
bool use_err_help;  // should the |err_help| list be shown?
// ~~~ End section 79 ~~~

// ~~~ Section 96 ~~~
int interrupt;        // should TeX pause for instructions?
bool ok_to_interrupt; // should interrupts be observed?
// ~~~ End section 96 ~~~

// ~~~ Section 104 ~~~
bool arith_error;  // has arithmetic overflow occurred recently?
scaled remainder_; // amount subtracted to get an exact division
// ~~~ End section 104 ~~~

// ~~~ Section 115 ~~~
pointer temp_ptr; // a pointer variable for occasional emergency use
// ~~~ End section 115 ~~~

// ~~~ Section 116 ~~~
memory_word mem[MEM_MAX + 1]; // the big dynamic storage area
pointer lo_mem_max;           // the largest location of variable-size memory in use
pointer hi_mem_min;           // the smallest location of one-word memory in use
// ~~~ End section 116 ~~~

// ~~~ Section 117 ~~~
int var_used, dyn_used; // how much memory is in use
// ~~~ End section 117 ~~~

// ~~~ Section 118 ~~~
pointer avail;   // head of the list of available one-word nodes
pointer mem_end; // the last one-word node used in |mem|
// ~~~ End section 118 ~~~

// ~~~ Section 124 ~~~
pointer rover; // points to some node in the list of empties
// ~~~ End section 124 ~~~

// ~~~ Section 165 ~~~
#ifdef DEBUG
bool free_cells[MEM_MAX + 1]; // free_cells
bool was_free[MEM_MAX + 1];   // previously free cells
pointer was_mem_end, was_lo_max, was_hi_min; // previous |mem_end|, |lo_mem_max|, and |hi_mem_min|
bool panicking; // do we want to check memory constantly?
#endif
// ~~~ End section 165 ~~~

// ~~~ Section 173 ~~~
int font_in_short_display; // an internal font number
// ~~~ End section 173 ~~~

// ~~~ Section 181 ~~~
int depth_threshold; // maximum nesting depth in box displays
int breadth_max;    // maximum number of items shown at the same list level
// ~~~ End section 181 ~~~

// ~~~ Section 213 ~~~
list_state_record nest[NEST_SIZE + 1];
int nest_ptr;               // first unused location of |nest|
int max_nest_stack;         // maximum of |nest_ptr| when pushing
list_state_record cur_list; // top "top" semantic nest
int shown_mode;             // most recent mode shown by \tracingcommands
// ~~~ End section 213 ~~~

// ~~~ Section 246 ~~~
int old_setting;
int sys_time, sys_day, sys_month, sys_year; // date and time supplied by external system
// ~~~ End section 246 ~~~

// ~~~ Section 253 ~~~
memory_word eqtb0[EQTB_SIZE - ACTIVE_BASE + 1];
memory_word *eqtb = eqtb0 - ACTIVE_BASE;
quarterword xeq_level0[EQTB_SIZE - INT_BASE + 1];
quarterword *xeq_level = xeq_level0 - INT_BASE;
// ~~~ End section 253 ~~~

// ~~~ Section 256 ~~~
memory_word hash0[UNDEFINED_CONTROL_SEQUENCE - HASH_BASE]; // the hash table
memory_word *hash = hash0 - HASH_BASE;
pointer hash_used;            // allocation pointer for |hash|
bool no_new_control_sequence; // are new identifiers legal?
int cs_count;                 // total number of known identifiers
// ~~~ End section 256 ~~~

// ~~~ Section 271 ~~~
memory_word save_stack[SAVE_SIZE + 1];
int save_ptr;          // first unused entry on |save_stack|
int max_save_stack;    // maximum usage of save stack
quarterword cur_level; // current nesting level for groups
int cur_group;         // current group type
int cur_boundary;      // where the current level begins
// ~~~ End section 271 ~~~

// ~~~ Section 286 ~~~
int mag_set; // if nonzero, this magnification should be used henceforth
// ~~~ End section 286 ~~~

// ~~~ Section 297 ~~~
eight_bits cur_cmd; // current command set by |get_next|
halfword   cur_chr; // operand of current command
pointer    cur_cs;  // control sequence found here, zero if none found
halfword   cur_tok; // packed representative of |cur_cmd| and |cur_chr|
// ~~~ End section 297 ~~~

// ~~~ Section 301 ~~~
in_state_record input_stack[STACK_SIZE + 1];
int input_ptr;             // first unused location of |input_stack|
int max_in_stack;          // largest value of |input_ptr| when pushing
in_state_record cur_input; // the "top" input state, according to convention (1)
// ~~~ End section 301 ~~~

// ~~~ Section 304 ~~~
int in_open;     // the number of lines in the buffer, less one
int open_parens; // the number of open text files
alpha_file input_file0[MAX_IN_OPEN];
alpha_file *input_file = input_file0 - 1;
int line; // current line number in the current source file
int line_stack0[MAX_IN_OPEN];
int *line_stack = line_stack0 - 1;
// ~~~ End section 304 ~~~

// ~~~ Section 305 ~~~
int scanner_status;    // can a subfile end now?
pointer warning_index; // identifier relevant to non-|NORMAL| scanner status
pointer def_ref;       // reference count of token list being defined
// ~~~ End section 305 ~~~

// ~~~ Section 308 ~~~
pointer param_stack[PARAM_SIZE + 1]; // token list pointers for parameters
int param_ptr;                       // first unused entry in |param_stack|
int max_param_stack;                 // largest value of |param_ptr|, will be |<= PARAM_SIZE + 9|
// ~~~ End section 308 ~~~

// ~~~ Section 309 ~~~
int align_state; // group level with respect to current alignment
// ~~~ End section 309 ~~~

// ~~~ Section 310 ~~~
int base_ptr; // shallowest level shown by |show_context|
// ~~~ End section 310 ~~~

// ~~~ Section 333 ~~~
pointer par_loc;    // location of \par in eqtb
halfword par_token; // token representing \par
// ~~~ End section 333 ~~~

// ~~~ Section 361 ~~~
bool force_eof; // should the next \input be aborted early?
// ~~~ End section 361 ~~~

// ~~~ Section 382 ~~~
pointer cur_mark[SPLIT_BOT_MARK_CODE + 1]; // token lists for marks
// ~~~ End section 382 ~~~

// ~~~ Section 387 ~~~
int long_state; // governs the acceptance of \par
// ~~~ End section 387 ~~~

// ~~~ Section 388 ~~~
pointer pstack[9]; // arguments supplied to a macro
// ~~~ End section 388 ~~~

// ~~~ Section 410 ~~~
int cur_val;       // value returned by numeric scanners
int cur_val_level; // the "level" of this value
// ~~~ End section 410 ~~~

// ~~~ Section 438 ~~~
small_number radix; // |scan_int| sets this to 8, 10, 16, or zero
// ~~~ End section 438 ~~~

// ~~~ Section 447 ~~~
int cur_order; // order of infinity found by |scan_dimen|
// ~~~ End section 447 ~~~

// ~~~ Section 480 ~~~
alpha_file read_file[16]; // used for \read
int read_open[17];        // state of read_file[n]
// ~~~ End section 480 ~~~

// ~~~ Section 489 ~~~
pointer cond_ptr;    // top of the condition stack
int if_limit;        // upper bound on |fi_or_else| codes
small_number cur_if; // type of conditional being worked on
int if_line;         // line where that conditional began
// ~~~ End section 489 ~~~

// ~~~ Section 493 ~~~
int skip_line; // skipping began here
// ~~~ End section 493 ~~~

// ~~~ Section 512 ~~~
str_number cur_name; // name of file just scanned
str_number cur_area; // file area just scanned, or ""
str_number cur_ext;  // file extension just scanned, or ""
// ~~~ End section 512 ~~~

// ~~~ Section 513 ~~~
pool_pointer area_delimiter; // the most recent '>' or ':', if any
pool_pointer ext_delimiter;  // the relevant '.', if any
// ~~~ End section 513 ~~~

// ~~~ Section 520 ~~~
char tex_format_default[FORMAT_DEFAULT_LENGTH];
// ~~~ End section 520 ~~~

// ~~~ Section 527 ~~~
bool name_in_progress; // is a file name being scanned?
str_number job_name;   // principal file name
bool log_opened;       // has the transcript file been opened?
// ~~~ End section 527 ~~~

// ~~~ Section 532 ~~~
byte_file dvi_file;          // the device-independent output goes here
str_number output_file_name; // full name of the output file
str_number log_name;         // full name of the log file
// ~~~ End section 532 ~~~

// ~~~ Section 539 ~~~
byte_file tfm_file;
// ~~~ End section 539 ~~~

// ~~~ Section 549 ~~~
memory_word font_info[FONT_MEM_SIZE + 1]; // the big collection of font data
font_index fmem_ptr;                      // first unused word of |font_info|
internal_font_number font_ptr;            // largest internal font number in use
memory_word font_check[FONT_MAX + 1];     // check sum
scaled font_size[FONT_MAX + 1];           // "at" size
scaled font_dsize[FONT_MAX + 1];          // "design" size
font_index font_params[FONT_MAX + 1];     // how many font parameters are present
str_number font_name[FONT_MAX + 1];       // name of the font
str_number font_area[FONT_MAX + 1];       // area of the font
eight_bits font_bc[FONT_MAX + 1];         // beginning (smallest) character code
eight_bits font_ec[FONT_MAX + 1];         // ending (largest) character code
pointer font_glue[FONT_MAX + 1];          // glue specification for interword space, |null| if not allocated
bool font_used[FONT_MAX + 1];             // has a character from this font actually appeared in the output?
int hyphen_char[FONT_MAX + 1];            // current \hyphenchar values
int skew_char[FONT_MAX + 1];              // current \skewchar values
font_index bchar_label[FONT_MAX + 1];     // start of |lig_kern| program for left boundary character, |NON_ADDRESS| if there is none
int font_bchar[FONT_MAX + 1];        // boundary character, |NON_CHAR| if there is none
int font_false_bchar[FONT_MAX + 1];  // |font_bchar| if it doesn't exist in the font, otherwise |NON_CHAR|
// ~~~ End section 549 ~~~

// ~~~ Section 550 ~~~
int char_base[FONT_MAX+ 1];      // base addresses for |char_info|
int width_base[FONT_MAX + 1];    // base addresses for widths
int height_base[FONT_MAX + 1];   // base addresses for heights
int depth_base[FONT_MAX + 1];    // base addresses for depths
int italic_base[FONT_MAX + 1];   // base addresses for italic corrections
int lig_kern_base[FONT_MAX + 1]; // base addresses for ligature/kerning programs
int kern_base[FONT_MAX + 1];     // base addresses for kerns
int exten_base[FONT_MAX + 1];    // base addresses for extensible recipes
int param_base[FONT_MAX + 1];    // base addresses for font parameters
// ~~~ End section 550 ~~~

// ~~~ Section 555 ~~~
memory_word null_character; // nonexistent character information
// ~~~ End section 555 ~~~

// ~~~ Section 592 ~~~
int total_pages;    // the number of pages that have been shipped out
scaled max_v;       // maximum height-plus-depth of pages shipped so far
scaled max_h;       // maximum width of pages shipped so far
int max_push;       // deepest nesting of |PUSH| commands encountered so far
int last_bop;       // location of previous |BOP| in the `DVI` output
int dead_cycles;    // recent outputs that didn't ship anything out
bool doing_leaders; // are we inside a leader box?

quarterword c, f;                 // character and font in current |CHAR_NODE|
scaled rule_ht, rule_dp, rule_wd; // size of current rule being output
pointer g;                        // current glue specification
int lq, lr;                       // quantities used in calculations for leaders
// ~~~ End section 592 ~~~

// ~~~ Section 595 ~~~
eight_bits dvi_buf[DVI_BUF_SIZE + 1]; // buffer for `DVI` output
int half_buf;   // half of |DVI_BUF_SIZE|
int dvi_limit;  // end of the current half buffer
int dvi_ptr;    // the next available buffer address
int dvi_offset; // |DVI_BUF_SIZE| times the number of times the output buffer has been fully emptied
int dvi_gone;   // the number of bytes already output to |dvi_file|
// ~~~ End section 595 ~~~

// ~~~ Section 605 ~~~
pointer down_ptr, right_ptr; // heads of the down and right stacks
// ~~~ End section 605 ~~~

// ~~~ Section 616 ~~~
scaled dvi_h, dvi_v;        // a `DVI` reader program thinks we are here
scaled cur_h, cur_v;        // TeX thinks we are here
internal_font_number dvi_f; // the current font
int cur_s;                  // current depth of output box nesting, initially -1
// ~~~ End section 616 ~~~

// ~~~ Section 646 ~~~
scaled total_stretch[4], total_shrink[4]; // glue found by |hpack| or |vpack|
int last_badness; // badness of the most recently packaged box
// ~~~ End section 646 ~~~

// ~~~ Section 647 ~~~
pointer adjust_tail; // tail of adjustment list
// ~~~ End section 647 ~~~

// ~~~ Section 661 ~~~
int pack_begin_line; // source file line where the current paragraph or alignment began; a negative value denotes alignment
// ~~~ End section 661 ~~~

// ~~~ Section 684 ~~~
memory_word empty_field;
memory_word null_delimiter;
// ~~~ End section 684 ~~~

// ~~~ Section 719 ~~~
pointer      cur_mlist; // beginning of mlist to be translated
small_number cur_style; // style code at current place in the list
small_number cur_size;  // size code corresponding to |cur_style|
scaled       cur_mu;    // the math unit width corresponding to |cur_size|
bool mlist_penalties;   // should |mlist_to_hlist| insert penalties?
// ~~~ End section 719 ~~~

// ~~~ Section 724 ~~~
internal_font_number cur_f; // the |font| field of a |MATH_CHAR|
quarterword cur_c;          // the |character| field of a |MATH_CHAR|
memory_word cur_i;          // the |char_info| of a |MATH_CHAR|, or a lig/kern instruction
// ~~~ End section 724 ~~~

// ~~~ Section 770 ~~~
pointer cur_align;          // current position in preamble list
pointer cur_span;           // start of currently spanned columns in preamble list
pointer cur_loop;           // place to copy when extending a periodic preamble
pointer align_ptr;          // most recently pushed-down alignment stack node
pointer cur_head, cur_tail; // adjustment list pointers
// ~~~ End section 770 ~~~

// ~~~ Section 814 ~~~
pointer just_box; // the |HLIST_NODE| for the last line of the new paragraph
// ~~~ End section 814 ~~~

// ~~~ Section 821 ~~~
pointer passive;      // most recent node on passive list
pointer printed_node; // most recent node that has been printed
halfword pass_number; // the number of passive nodes allocated on this pass
// ~~~ End section 821 ~~~

// ~~~ Section 823 ~~~
// distance from first active node to |cur_p|
scaled active_width0[6];
scaled *active_width = active_width0 - 1;

// distance from current active node
scaled cur_active_width0[6];
scaled *cur_active_width = cur_active_width0 - 1;

// length of an "empty" line
scaled background0[6];
scaled *background = background0 - 1;

// length being computed after current break
scaled break_width0[6];
scaled *break_width = break_width0 - 1;
// ~~~ End section 823 ~~~

// ~~~ Section 825 ~~~
bool no_shrink_error_yet; // have we complained about infinite shrinkage?
// ~~~ End section 825 ~~~

// ~~~ Section 828 ~~~
pointer cur_p;    // the current breakpoint under consideration
bool second_pass; // is this our second attempt to break this paragraph?
bool final_pass;  // is this our final attempt to break this paragraph?
int threshold;    // maximum badness on feasible lines
// ~~~ End section 828 ~~~

// ~~~ Section 833 ~~~
int minimal_demerits[4];  // best total demerits known for current line class and position, given the fitness
int minimum_demerits;     // best total demerits known for current line class and position
pointer best_place[4];    // how to achieve |minimal_demerits|
halfword best_pl_line[4]; // corresponding line number
// ~~~ End section 833 ~~~

// ~~~ Section 839 ~~~
scaled disc_width; // the length of discretionary material preceding a break
// ~~~ End section 839 ~~~

// ~~~ Section 847 ~~~
halfword easy_line;         // line numbers |> easy_line| are equivalent in break nodes
halfword last_special_line; // line numbers |> last_special_line| all have the same width
scaled first_width;         // the width of all lines |<= last_special_line|, if no \parshape has been specified
scaled second_width;        // the width of all lines |> last_special_line|
scaled first_indent;        // left margin to go with |first_width|
scaled second_indent;       // left margin to go with |second_width|
// ~~~ End section 847 ~~~

// ~~~ Section 872 ~~~
pointer best_bet;     // use this passive node and its predecessors
int fewest_demerits;  // the demerits associated with |best_bet|
halfword best_line;   // line number following the last line of the new paragraph
int actual_looseness; // the difference between |line_number(best_bet)| and the optimum |best_line|
int line_diff;        // the difference between the current line number and the optimum |best_line|
// ~~~ End section 872 ~~~

// ~~~ Section 892 ~~~
quarterword hc[66];                       // word to be hyphenated
small_number hn;                          // the number of positions occupied in |hc|; not always a |small_number|
pointer ha, hb;                           // nodes |ha .. hb| should be replaced by the hyphenated result
internal_font_number hf;                  // font number of the letters in |hc|
quarterword hu[64];                       // like |hc|, before conversion to lowercase
int hyf_char;                             // hyphen character of the relevant font
ASCII_code cur_lang, init_cur_lang;       // current hyphenation table of interest
int l_hyf, r_hyf, init_l_hyf, init_r_hyf; // limits on fragment sizes
halfword hyf_bchar;                       // boundary character after c_n
// ~~~ End section 892 ~~~

// ~~~ Section 900 ~~~
quarterword hyf[65]; // odd values indicate discretionary hyphens
pointer init_list;   // list of punctuation characters preceding the word
bool init_lig;       // does |init_list| represent a ligature?
bool init_lft;       // if so, did the ligature involve a left boundary?
// ~~~ End section 900 ~~~

// ~~~ Section 905 ~~~
small_number hyphen_passed; // first hyphen in a ligature, if any
// ~~~ End section 905 ~~~

// ~~~ Section 907 ~~~
halfword cur_l, cur_r; // characters before and after the cursor
pointer cur_q;         // where a ligature should be detached
pointer lig_stack;     // unfinished business to the right of the cursor
bool ligature_present; // should a ligature node be made for |cur_l|?
bool lft_hit, rt_hit;  // did we hit a ligature with a boundary character?
// ~~~ End section 907 ~~~

// ~~~ Section 921 ~~~
// |trie_link|, |trie_char|, |trie_op|
memory_word trie[TRIE_SIZE + 1];

// position |k - j| of $n_j$
small_number hyf_distance0[TRIE_OP_SIZE];
small_number *hyf_distance = hyf_distance0 - 1; 

// value of $n_j$
small_number hyf_num0[TRIE_OP_SIZE];
small_number *hyf_num = hyf_num0 - 1;

// continuation code
quarterword hyf_next0[TRIE_OP_SIZE];
quarterword *hyf_next = hyf_next0 - 1;

// offset for current language
int op_start[256];
// ~~~ End section 921 ~~~

// ~~~ Section 926 ~~~
str_number hyph_word[HYPH_SIZE + 1]; // exception words
pointer hyph_list[HYPH_SIZE + 1];    // lists of hyphen positions
int hyph_count;                      // the number of words in the exception dictionary
// ~~~ End section 926 ~~~

// ~~~ Section 943 ~~~
#ifdef INIT
// trie op codes for quadruples
int trie_op_hash0[2*TRIE_OP_SIZE + 1];
int *trie_op_hash = trie_op_hash0 + TRIE_OP_SIZE;

// largest opcode used so far for this language
quarterword trie_used[256];

// language part of a hashed quadruple
ASCII_code trie_op_lang0[TRIE_OP_SIZE];
ASCII_code *trie_op_lang = trie_op_lang0 - 1;

// opcode corresponding to a hashed quadruple
quarterword trie_op_val0[TRIE_OP_SIZE];
quarterword *trie_op_val = trie_op_val0 - 1;

// number of stored ops so far
int trie_op_ptr;
#endif
// ~~~ End section 943 ~~~

// ~~~ Section 947 ~~~
#ifdef INIT
// characters to match
unsigned char trie_c[TRIE_SIZE + 1];

// operations to perform
quarterword trie_o[TRIE_SIZE + 1];

// left subtrie links
int trie_l[TRIE_SIZE + 1];

// right subtrie links
int trie_r[TRIE_SIZE + 1];

// the number of nodes in the trie
int trie_ptr; 

// used to identify equivalent subtries
int trie_hash[TRIE_SIZE + 1];
#endif
// ~~~ End section 947 ~~~

// ~~~ Section 950 ~~~
#ifdef INIT
// does a family start here?
bool trie_taken0[TRIE_SIZE];
bool *trie_taken = trie_taken0 - 1;
int trie_min[256];   // the first possible slot for each character
int trie_max;        // largest location used in |trie|
bool trie_not_ready; // is the trie still in linked form?
#endif
// ~~~ End section 950 ~~~

// ~~~ Section 971 ~~~
scaled best_height_plus_depth; // height of the best box, without stretching or shrinking
// ~~~ End section 971 ~~~

// ~~~ Section 980 ~~~
pointer page_tail;       // the final node on the current page
int     page_contents;   // what is on the current page so far?
scaled  page_max_depth;  // maximum box depth on page being built
pointer best_page_break; // break here to get the best page known so far
int     least_page_cost; // the score for this currently best page
scaled  best_size;       // its |page_goal|
// ~~~ End section 980 ~~~

// ~~~ Section 982 ~~~
scaled  page_so_far[8];   // height and glue of the current page
pointer last_glue;        // used to implement \lastskip
int     last_penalty;     // used to implement \lastpenalty
scaled  last_kern;        // used to implement \lastkern
int     insert_penalties; // sum of the penalties for insertions that were held over
// ~~~ End section 982 ~~~

// ~~~ Section 989 ~~~
bool output_active; // are we in the midst of an output routine?
// ~~~ End section 989 ~~~

// ~~~ Section 1032 ~~~
internal_font_number main_f; // the current font
memory_word main_i;          // character information bytes for |cur_l|
memory_word main_j;          // ligature/kern command
int main_k;                  // index into |font_info|
pointer main_p;              // temporary register for list manipulation
int main_s;                  // space factor value
halfword bchar;              // boundary character of current font, or |NON_CHAR|
halfword false_bchar;        // nonexistent character matching |bchar|, or |NON_CHAR|
bool cancel_boundary;        // should the left boundary be ignored?
bool ins_disc;               // should we insert a discretionary node?
// ~~~ End section 1032 ~~~

// ~~~ Section 1074 ~~~
pointer cur_box; // box to be placed into its context
// ~~~ End section 1074 ~~~

// ~~~ Section 1266 ~~~
halfword after_token; // zero, or a saved token
// ~~~ End section 1266 ~~~

// ~~~ Section 1281 ~~~
bool long_help_seen; // has the long \errmessage help been used?
// ~~~ End section 1281 ~~~

// ~~~ Section 1299 ~~~
str_number format_ident;
// ~~~ End section 1299 ~~~

// ~~~ Section 1305 ~~~
word_file fmt_file; // for input or output of format information
// ~~~ End section 1305 ~~~

// ~~~ Section 1342 ~~~
alpha_file write_file[16];
bool write_open[18];
// ~~~ End section 1342 ~~~

// ~~~ Section 1345 ~~~
pointer write_loc; // |eqtb| address of \write
// ~~~ End section 1345 ~~~
// ~~~ End section 13 ~~~
// ~~~ End section 4 ~~~
