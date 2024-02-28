# Section 1380

For this C implementation, all global variables need to be declared as `extern`.

For simplicity, they are declared here in one shot.

```c include/tex.h
// ~~~ Section 13 ~~~
extern int bad; // is some "constant" wrong?

// ~~~ Section 26 ~~~
extern char name_of_file[FILE_NAME_SIZE + 1];
extern int name_length; // this many characters are actually relevant in |name_of_file| (the rest are blank)
// ~~~ End section 26 ~~~

// ~~~ Section 30 ~~~
extern ASCII_code buffer[BUF_SIZE + 1]; // lines of character being read
extern int first;                       // the first unused position in |buffer|
extern int last;                        // end of the line just input to |buffer|
extern int max_buf_stack;               // largest index used in |buffer|
// ~~~ End section 30 ~~~

// ~~~ Section 39 ~~~
extern ASCII_code str_pool[POOL_SIZE + 1];      // the characters
extern pool_pointer str_start[MAX_STRINGS + 1]; // the starting pointers
extern pool_pointer pool_ptr;                   // first unused position in |str_pool|
extern str_number str_ptr;                      // number of the current string being created
extern pool_pointer init_pool_ptr;              // the starting value of |pool_ptr|
extern str_number init_str_ptr;                 // the starting value of |str_ptr|
// ~~~ End section 39 ~~~

// ~~~ Section 54 ~~~
extern alpha_file log_file;                  // transcript of TeX session
extern int selector;                         // where to print a message
extern unsigned char dig[23];                // digits in a number being output
extern int tally;                            // the number of characters recently printed
extern int term_offset;                      // the number of characters on the current terminal line
extern int file_offset;                      // the number of characters on the current file line
extern ASCII_code trick_buf[ERROR_LINE + 1]; // circular buffer for pseudoprinting
extern int trick_count;                      // threshold for pseudoprinting, explained later
extern int first_count;                      // another variable for pseudoprinting
// ~~~ End section 54 ~~~

// ~~~ Section 73 ~~~
extern int interaction; // current level of interaction
// ~~~ End section 73 ~~~

// ~~~ Section 76 ~~~
extern bool deletions_allowed; // is it safe for |error| to call |get_token|?
extern bool set_box_allowed;   // is it safe to do a \setbox assignment?
extern int history;            // has the source input been clean so far?
extern int error_count;        // the number of scrolled errors since the last paragraph ended
// ~~~ End section 76 ~~~

// ~~~ Section 79 ~~~
extern char *help_line[6]; // helps for the next |error|
extern int help_ptr;       // the number of help lines present
extern bool use_err_help;  // should the |err_help| list be shown?
// ~~~ End section 79 ~~~

// ~~~ Section 96 ~~~
extern int interrupt;        // should TeX pause for instructions?
extern bool ok_to_interrupt; // should interrupts be observed?
// ~~~ End section 96 ~~~

// ~~~ Section 104 ~~~
extern bool arith_error;  // has arithmetic overflow occurred recently?
extern scaled remainder_; // amount subtracted to get an exact division
// ~~~ End section 104 ~~~

// ~~~ Section 115 ~~~
extern pointer temp_ptr; // a pointer variable for occasional emergency use
// ~~~ End section 115 ~~~

// ~~~ Section 116 ~~~
extern memory_word mem[MEM_MAX + 1]; // the big dynamic storage area
extern pointer lo_mem_max; // the largest location of variable-size memory in use
extern pointer hi_mem_min; // the smallest location of one-word memory in use
// ~~~ End section 116 ~~~

// ~~~ Section 117 ~~~
extern int var_used, dyn_used; // how much memory is in use
// ~~~ End section 117 ~~~

// ~~~ Section 118 ~~~
extern pointer avail;   // head of the list of available one-word nodes
extern pointer mem_end; // the last one-word node used in |mem|
// ~~~ End section 118 ~~~

// ~~~ Section 124 ~~~
extern pointer rover; // points to some node in the list of empties
// ~~~ End section 124 ~~~

// ~~~ Section 165 ~~~
#ifdef DEBUG
extern bool free_cells[MEM_MAX + 1]; // free_cells
extern bool was_free[MEM_MAX + 1]; // previously free cells
extern pointer was_mem_end, was_lo_max, was_hi_min; // previous |mem_end|, |lo_mem_max|, and |hi_mem_min|
extern bool panicking; // do we want to check memory constantly?
#endif
// ~~~ End section 165 ~~~

// ~~~ Section 173 ~~~
extern int font_in_short_display; // an internal font number
// ~~~ End section 173 ~~~

// ~~~ Section 181 ~~~
extern int depth_threshold; // maximum nesting depth in box displays
extern int breadth_max;    // maximum number of items shown at the same list level
// ~~~ End section 181 ~~~

// ~~~ Section 213 ~~~
extern list_state_record nest[NEST_SIZE + 1];
extern int nest_ptr;               // first unused location of |nest|
extern int max_nest_stack;         // maximum of |nest_ptr| when pushing
extern list_state_record cur_list; // top "top" semantic nest
extern int shown_mode;             // most recent mode shown by \tracingcommands
// ~~~ End section 213 ~~~

// ~~~ Section 246 ~~~
extern int old_setting;
extern int sys_time, sys_day, sys_month, sys_year; // date and time supplied by external system
// ~~~ End section 246 ~~~

// ~~~ Section 253 ~~~
extern memory_word eqtb0[EQTB_SIZE - ACTIVE_BASE + 1];
extern memory_word *eqtb;
extern quarterword xeq_level0[EQTB_SIZE - INT_BASE + 1];
extern quarterword *xeq_level;
// ~~~ End section 253 ~~~

// ~~~ Section 256 ~~~
extern memory_word hash0[UNDEFINED_CONTROL_SEQUENCE - HASH_BASE]; // the hash table
extern memory_word *hash;
extern pointer hash_used;            // allocation pointer for |hash|
extern bool no_new_control_sequence; // are new identifiers legal?
extern int cs_count;                 // total number of known identifiers
// ~~~ End section 256 ~~~

// ~~~ Section 271 ~~~
extern memory_word save_stack[SAVE_SIZE + 1];
extern int save_ptr;          // first unused entry on |save_stack|
extern int max_save_stack;    // maximum usage of save stack
extern quarterword cur_level; // current nesting level for groups
extern int cur_group;         // current group type
extern int cur_boundary;      // where the current level begins
// ~~~ End section 271 ~~~

// ~~~ Section 286 ~~~
extern int mag_set; // if nonzero, this magnification should be used henceforth
// ~~~ End section 286 ~~~

// ~~~ Section 297 ~~~
extern eight_bits cur_cmd; // current command set by |get_next|
extern halfword cur_chr;   // operand of current command
extern pointer cur_cs;     // control sequence found here, zero if none found
extern halfword cur_tok;   // packed representative of |cur_cmd| and |cur_chr|
// ~~~ End section 297 ~~~

// ~~~ Section 301 ~~~
extern in_state_record input_stack[STACK_SIZE + 1];
extern int input_ptr;             // first unused location of |input_stack|
extern int max_in_stack;          // largest value of |input_ptr| when pushing
extern in_state_record cur_input; // the ``top'' input state, according to convention (1)
// ~~~ End section 301 ~~~

// ~~~ Section 304 ~~~
extern int in_open; // the number of lines in the buffer, less one
extern int open_parens; // the number of open text files
extern alpha_file input_file0[MAX_IN_OPEN];
extern alpha_file *input_file;
extern int line; // current line number in the current source file
extern int line_stack0[MAX_IN_OPEN];
extern int *line_stack;
// ~~~ End section 304 ~~~

// ~~~ Section 305 ~~~
extern int scanner_status;    // can a subfile end now?
extern pointer warning_index; // identifier relevant to non-|NORMAL| scanner status
extern pointer def_ref;       // reference count of token list being defined
// ~~~ End section 305 ~~~

// ~~~ Section 308 ~~~
extern pointer param_stack[PARAM_SIZE + 1]; // token list pointers for parameters
extern int param_ptr;                       // first unused entry in |param_stack|
extern int max_param_stack;                 // largest value of |param_ptr|, will be |<= PARAM_SIZE + 9|
// ~~~ End section 308 ~~~

// ~~~ Section 309 ~~~
extern int align_state; // group level with respect to current alignment
// ~~~ End section 309 ~~~

// ~~~ Section 310 ~~~
extern int base_ptr; // shallowest level shown by |show_context|
// ~~~ End section 310 ~~~

// ~~~ Section 333 ~~~
extern pointer par_loc;    // location of \par in eqtb
extern halfword par_token; // token representing \par
// ~~~ End section 333 ~~~

// ~~~ Section 361 ~~~
extern bool force_eof; // should the next \input be aborted early?
// ~~~ End section 361 ~~~

// ~~~ Section 382 ~~~
extern pointer cur_mark[SPLIT_BOT_MARK_CODE + 1]; // token lists for marks
// ~~~ End section 382 ~~~

// ~~~ Section 387 ~~~
extern int long_state; // governs the acceptance of \par
// ~~~ End section 387 ~~~

// ~~~ Section 388 ~~~
extern pointer pstack[9]; // arguments supplied to a macro
// ~~~ End section 388 ~~~

// ~~~ Section 410 ~~~
extern int cur_val; // value returned by numeric scanners
extern int cur_val_level; // the "level" of this value
// ~~~ End section 410 ~~~

// ~~~ Section 438 ~~~
extern small_number radix; // |scan_int| sets this to 8, 10, 16, or zero
// ~~~ End section 438 ~~~

// ~~~ Section 447 ~~~
extern int cur_order; // order of infinity found by |scan_dimen|
// ~~~ End section 447 ~~~

// ~~~ Section 480 ~~~
extern alpha_file read_file[16]; // used for \read
extern int read_open[17];        // state of read_file[n]
// ~~~ End section 480 ~~~

// ~~~ Section 489 ~~~
extern pointer cond_ptr;    // top of the condition stack
extern int if_limit;        // upper bound on |fi_or_else| codes
extern small_number cur_if; // type of conditional being worked on
extern int if_line;         // line where that conditional began
// ~~~ End section 489 ~~~

// ~~~ Section 493 ~~~
extern int skip_line; // skipping began here
// ~~~ End section 493 ~~~

// ~~~ Section 512 ~~~
extern str_number cur_name; // name of file just scanned
extern str_number cur_area; // file area just scanned, or ""
extern str_number cur_ext;  // file extension just scanned, or ""
// ~~~ End section 512 ~~~

// ~~~ Section 513 ~~~
extern pool_pointer area_delimiter; // the most recent '>' or ':', if any
extern pool_pointer ext_delimiter;  // the relevant '.', if any
// ~~~ End section 513 ~~~

// ~~~ Section 520 ~~~
extern char tex_format_default[FORMAT_DEFAULT_LENGTH];
// ~~~ End section 520 ~~~

// ~~~ Section 527 ~~~
extern bool name_in_progress; // is a file name being scanned?
extern str_number job_name;   // principal file name
extern bool log_opened;       // has the transcript file been opened?
// ~~~ End section 527 ~~~

// ~~~ Section 532 ~~~
extern byte_file dvi_file;          // the device-independent output goes here
extern str_number output_file_name; // full name of the output file
extern str_number log_name;         // full name of the log file
// ~~~ End section 532 ~~~

// ~~~ Section 539 ~~~
extern byte_file tfm_file;
// ~~~ End section 539 ~~~

// ~~~ Section 549 ~~~
extern memory_word font_info[FONT_MEM_SIZE + 1]; // the big collection of font data
extern font_index fmem_ptr;                      // first unused word of |font_info|
extern internal_font_number font_ptr;            // largest internal font number in use
extern memory_word font_check[FONT_MAX + 1];     // check sum
extern scaled font_size[FONT_MAX + 1];           // "at" size
extern scaled font_dsize[FONT_MAX + 1];          // "design" size
extern font_index font_params[FONT_MAX + 1];     // how many font parameters are present
extern str_number font_name[FONT_MAX + 1];       // name of the font
extern str_number font_area[FONT_MAX + 1];       // area of the font
extern eight_bits font_bc[FONT_MAX + 1];         // beginning (smallest) character code
extern eight_bits font_ec[FONT_MAX + 1];         // ending (largest) character code
extern pointer font_glue[FONT_MAX + 1];          // glue specification for interword space, |null| if not allocated
extern bool font_used[FONT_MAX + 1];             // has a character from this font actually appeared in the output?
extern int hyphen_char[FONT_MAX + 1];            // current \hyphenchar values
extern int skew_char[FONT_MAX + 1];              // current \skewchar values
extern font_index bchar_label[FONT_MAX + 1];     // start of |lig_kern| program for left boundary character, |NON_ADDRESS| if there is none
extern int font_bchar[FONT_MAX + 1];        // boundary character, |NON_CHAR| if there is none
extern int font_false_bchar[FONT_MAX + 1];  // |font_bchar| if it doesn't exist in the font, otherwise |NON_CHAR|
// ~~~ End section 549 ~~~

// ~~~ Section 550 ~~~
extern int char_base[FONT_MAX+ 1];      // base addresses for |char_info|
extern int width_base[FONT_MAX + 1];    // base addresses for widths
extern int height_base[FONT_MAX + 1];   // base addresses for heights
extern int depth_base[FONT_MAX + 1];    // base addresses for depths
extern int italic_base[FONT_MAX + 1];   // base addresses for italic corrections
extern int lig_kern_base[FONT_MAX + 1]; // base addresses for ligature/kerning programs
extern int kern_base[FONT_MAX + 1];     // base addresses for kerns
extern int exten_base[FONT_MAX + 1];    // base addresses for extensible recipes
extern int param_base[FONT_MAX + 1];    // base addresses for font parameters
// ~~~ End section 550 ~~~

// ~~~ Section 555 ~~~
extern memory_word null_character; // nonexistent character information
// ~~~ End section 555 ~~~

// ~~~ Section 592 ~~~
extern int total_pages;    // the number of pages that have been shipped out
extern scaled max_v;       // maximum height-plus-depth of pages shipped so far
extern scaled max_h;       // maximum width of pages shipped so far
extern int max_push;       // deepest nesting of |PUSH| commands encountered so far
extern int last_bop;       // location of previous |BOP| in the `DVI` output
extern int dead_cycles;    // recent outputs that didn't ship anything out
extern bool doing_leaders; // are we inside a leader box?

extern quarterword c, f;                 // character and font in current |CHAR_NODE|
extern scaled rule_ht, rule_dp, rule_wd; // size of current rule being output
extern pointer g;                        // current glue specification
extern int lq, lr;                       // quantities used in calculations for leaders
// ~~~ End section 592 ~~~

// ~~~ Section 595 ~~~
extern eight_bits dvi_buf[DVI_BUF_SIZE + 1]; // buffer for `DVI` output
extern int half_buf; // half of |DVI_BUF_SIZE|
extern int dvi_limit; // end of the current half buffer
extern int dvi_ptr; // the next available buffer address
extern int dvi_offset; // |DVI_BUF_SIZE| times the number of times the output buffer has been fully emptied
extern int dvi_gone; // the number of bytes already output to |dvi_file|
// ~~~ End section 595 ~~~

// ~~~ Section 605 ~~~
extern pointer down_ptr, right_ptr; // heads of the down and right stacks
// ~~~ End section 605 ~~~

// ~~~ Section 616 ~~~
extern scaled dvi_h, dvi_v;        // a `DVI` reader program thinks we are here
extern scaled cur_h, cur_v;        // TeX thinks we are here
extern internal_font_number dvi_f; // the current font
extern int cur_s;                  // current depth of output box nesting, initially -1
// ~~~ End section 616 ~~~

// ~~~ Section 646 ~~~
extern scaled total_stretch[4], total_shrink[4]; // glue found by |hpack| or |vpack|
extern int last_badness; // badness of the most recently packaged box
// ~~~ End section 646 ~~~

// ~~~ Section 647 ~~~
extern pointer adjust_tail; // tail of adjustment list
// ~~~ End section 647 ~~~

// ~~~ Section 661 ~~~
extern int pack_begin_line; // source file line where the current paragraph or alignment began; a negative value denotes alignment
// ~~~ End section 661 ~~~

// ~~~ Section 684 ~~~
extern memory_word empty_field;
extern memory_word null_delimiter;
// ~~~ End section 684 ~~~

// ~~~ Section 719 ~~~
extern pointer cur_mlist;      // beginning of mlist to be translated
extern small_number cur_style; // style code at current place in the list
extern small_number cur_size;  // size code corresponding to |cur_style|
extern scaled cur_mu;          // the math unit width corresponding to |cur_size|
extern bool mlist_penalties;   // should |mlist_to_hlist| insert penalties?
// ~~~ End section 719 ~~~

// ~~~ Section 724 ~~~
extern internal_font_number cur_f; // the |font| field of a |MATH_CHAR|
extern quarterword cur_c; // the |character| field of a |MATH_CHAR|
extern memory_word cur_i; // the |char_info| of a |MATH_CHAR|, or a lig/kern instruction
// ~~~ End section 724 ~~~

// ~~~ Section 770 ~~~
extern pointer cur_align;          // current position in preamble list
extern pointer cur_span;           // start of currently spanned columns in preamble list
extern pointer cur_loop;           // place to copy when extending a periodic preamble
extern pointer align_ptr;          // most recently pushed-down alignment stack node
extern pointer cur_head, cur_tail; // adjustment list pointers
// ~~~ End section 770 ~~~

// ~~~ Section 814 ~~~
extern pointer just_box; // the |HLIST_NODE| for the last line of the new paragraph
// ~~~ End section 814 ~~~

// ~~~ Section 821 ~~~
extern pointer passive;      // most recent node on passive list
extern pointer printed_node; // most recent node that has been printed
extern halfword pass_number; // the number of passive nodes allocated on this pass
// ~~~ End section 821 ~~~

// ~~~ Section 823 ~~~
// distance from first active node to |cur_p|
extern scaled active_width0[6];
extern scaled *active_width;
// distance from current active node
extern scaled cur_active_width0[6];
extern scaled  *cur_active_width;
// length of an "empty" line
extern scaled background0[6];
extern scaled *background;
// length being computed after current break
extern scaled break_width0[6];
extern scaled *break_width;
// ~~~ End section 823 ~~~

// ~~~ Section 825 ~~~
extern bool no_shrink_error_yet; // have we complained about infinite shrinkage?
// ~~~ End section 825 ~~~

// ~~~ Section 828 ~~~
extern pointer cur_p;    // the current breakpoint under consideration
extern bool second_pass; // is this our second attempt to break this paragraph?
extern bool final_pass;  // is this our final attempt to break this paragraph?
extern int threshold;    // maximum badness on feasible lines
// ~~~ End section 828 ~~~

// ~~~ Section 833 ~~~
extern int minimal_demerits[4];  // best total demerits known for current line class and position, given the fitness
extern int minimum_demerits;     // best total demerits known for current line class and position
extern pointer best_place[4];    // how to achieve |minimal_demerits|
extern halfword best_pl_line[4]; // corresponding line number
// ~~~ End section 833 ~~~

// ~~~ Section 839 ~~~
extern scaled disc_width; // the length of discretionary material preceding a break
// ~~~ End section 839 ~~~

// ~~~ Section 847 ~~~
extern halfword easy_line;         // line numbers |> easy_line| are equivalent in break nodes
extern halfword last_special_line; // line numbers |> last_special_line| all have the same width
extern scaled first_width;         // the width of all lines |<= last_special_line|, if no \parshape has been specified
extern scaled second_width;        // the width of all lines |> last_special_line|
extern scaled first_indent;        // left margin to go with |first_width|
extern scaled second_indent;       // left margin to go with |second_width|
// ~~~ End section 847 ~~~

// ~~~ Section 872 ~~~
extern pointer best_bet;     // use this passive node and its predecessors
extern int fewest_demerits;  // the demerits associated with |best_bet|
extern halfword best_line;   // line number following the last line of the new paragraph
extern int actual_looseness; // the difference between |line_number(best_bet)| and the optimum |best_line|
extern int line_diff;        // the difference between the current line number and the optimum |best_line|
// ~~~ End section 872 ~~~

// ~~~ Section 892 ~~~
extern quarterword hc[66];                       // word to be hyphenated
extern small_number hn;                          // the number of positions occupied in |hc|; not always a |small_number|
extern pointer ha, hb;                           // nodes |ha .. hb| should be replaced by the hyphenated result
extern internal_font_number hf;                  // font number of the letters in |hc|
extern quarterword hu[64];                       // like |hc|, before conversion to lowercase
extern int hyf_char;                             // hyphen character of the relevant font
extern ASCII_code cur_lang, init_cur_lang;       // current hyphenation table of interest
extern int l_hyf, r_hyf, init_l_hyf, init_r_hyf; // limits on fragment sizes
extern halfword hyf_bchar;                       // boundary character after c_n
// ~~~ End section 892 ~~~

// ~~~ Section 900 ~~~
extern quarterword hyf[65]; // odd values indicate discretionary hyphens
extern pointer init_list;   // list of punctuation characters preceding the word
extern bool init_lig;       // does |init_list| represent a ligature?
extern bool init_lft;       // if so, did the ligature involve a left boundary?
// ~~~ End section 900 ~~~

// ~~~ Section 905 ~~~
extern small_number hyphen_passed; // first hyphen in a ligature, if any
// ~~~ End section 905 ~~~

// ~~~ Section 907 ~~~
extern halfword cur_l, cur_r; // characters before and after the cursor
extern pointer cur_q;         // where a ligature should be detached
extern pointer lig_stack;     // unfinished business to the right of the cursor
extern bool ligature_present; // should a ligature node be made for |cur_l|?
extern bool lft_hit, rt_hit;  // did we hit a ligature with a boundary character?
// ~~~ End section 907 ~~~

// ~~~ Section 921 ~~~
// |trie_link|, |trie_char|, |trie_op|
extern memory_word trie[TRIE_SIZE + 1];
// position |k - j| of $n_j$
extern small_number hyf_distance0[TRIE_OP_SIZE];
extern small_number *hyf_distance; 
// value of $n_j$
extern small_number hyf_num0[TRIE_OP_SIZE];
extern small_number *hyf_num;
// continuation code
extern quarterword hyf_next0[TRIE_OP_SIZE];
extern quarterword *hyf_next;
// offset for current language
extern int op_start[256];
// ~~~ End section 921 ~~~

// ~~~ Section 926 ~~~
extern str_number hyph_word[HYPH_SIZE + 1]; // exception words
extern pointer hyph_list[HYPH_SIZE + 1];    // lists of hyphen positions
extern int hyph_count;                      // the number of words in the exception dictionary
// ~~~ End section 926 ~~~

// ~~~ Section 943 ~~~
#ifdef INIT
// trie op codes for quadruples
extern int trie_op_hash0[2*TRIE_OP_SIZE + 1];
extern int *trie_op_hash;

// largest opcode used so far for this language
extern quarterword trie_used[256];

// language part of a hashed quadruple
extern ASCII_code trie_op_lang0[TRIE_OP_SIZE];
extern ASCII_code *trie_op_lang;

// opcode corresponding to a hashed quadruple
extern quarterword trie_op_val0[TRIE_OP_SIZE];
extern quarterword *trie_op_val;

// number of stored ops so far
extern int trie_op_ptr;
#endif
// ~~~ End section 943 ~~~

// ~~~ Section 947 ~~~
#ifdef INIT
// characters to match

extern unsigned char trie_c[TRIE_SIZE + 1];

// operations to perform
extern quarterword trie_o[TRIE_SIZE + 1];

// left subtrie links
extern int trie_l[TRIE_SIZE + 1];

// right subtrie links
extern int trie_r[TRIE_SIZE + 1];

// the number of nodes in the trie
extern int trie_ptr; 

// used to identify equivalent subtries
extern int trie_hash[TRIE_SIZE + 1];
#endif
// ~~~ End section 947 ~~~

// ~~~ Section 950 ~~~
#ifdef INIT
// does a family start here?
extern bool trie_taken0[TRIE_SIZE];
extern bool *trie_taken;
extern int trie_min[256];   // the first possible slot for each character
extern int trie_max;        // largest location used in |trie|
extern bool trie_not_ready; // is the trie still in linked form?
#endif
// ~~~ End section 950 ~~~

// ~~~ Section 971 ~~~
extern scaled best_height_plus_depth; // height of the best box, without stretching or shrinking
// ~~~ End section 971 ~~~

// ~~~ Section 980 ~~~
extern pointer page_tail;       // the final node on the current page
extern int page_contents;       // what is on the current page so far?
extern scaled page_max_depth;   // maximum box depth on page being built
extern pointer best_page_break; // break here to get the best page known so far
extern int least_page_cost;     // the score for this currently best page
extern scaled best_size;        // its |page_goal|
// ~~~ End section 980 ~~~

// ~~~ Section 982 ~~~
extern scaled page_so_far[8]; // height and glue of the current page
extern pointer last_glue;     // used to implement \lastskip
extern int last_penalty;      // used to implement \lastpenalty
extern scaled last_kern;      // used to implement \lastkern
extern int insert_penalties;  // sum of the penalties for insertions that were held over
// ~~~ End section 982 ~~~

// ~~~ Section 989 ~~~
extern bool output_active; // are we in the midst of an output routine?
// ~~~ End section 989 ~~~

// ~~~ Section 1032 ~~~
extern internal_font_number main_f; // the current font
extern memory_word main_i;          // character information bytes for |cur_l|
extern memory_word main_j;          // ligature/kern command
extern int main_k;                  // index into |font_info|
extern pointer main_p;              // temporary register for list manipulation
extern int main_s;                  // space factor value
extern halfword bchar;              // boundary character of current font, or |NON_CHAR|
extern halfword false_bchar;        // nonexistent character matching |bchar|, or |NON_CHAR|
extern bool cancel_boundary;        // should the left boundary be ignored?
extern bool ins_disc;               // should we insert a discretionary node?
// ~~~ End section 1032 ~~~

// ~~~ Section 1074 ~~~
extern pointer cur_box; // box to be placed into its context
// ~~~ End section 1074 ~~~

// ~~~ Section 1266 ~~~
extern halfword after_token; // zero, or a saved token
// ~~~ End section 1266 ~~~

// ~~~ Section 1281 ~~~
extern bool long_help_seen; // has the long \errmessage help been used?
// ~~~ End section 1281 ~~~

// ~~~ Section 1299 ~~~
extern str_number format_ident;
// ~~~ End section 1299 ~~~

// ~~~ Section 1305 ~~~
extern word_file fmt_file; // for input or output of format information
// ~~~ End section 1305 ~~~

// ~~~ Section 1342 ~~~
extern alpha_file write_file[16];
extern bool write_open[18];
// ~~~ End section 1342 ~~~

// ~~~ Section 1345 ~~~
extern pointer write_loc; // |eqtb| address of \write
// ~~~ End section 1345 ~~~
// ~~~ End section 13 ~~~
```
