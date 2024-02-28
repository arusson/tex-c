// ~~~ Section 113 ~~~
// ~~~ Start file |datastructures.h|, 1381 ~~~
#ifndef DATASTRUCTURES_H_
#define DATASTRUCTURES_H_

#include "tex.h"
// ~~~ End section 1381 ~~~

#define qqqq_b0(W) (W).qqqq[0]
#define qqqq_b1(W) (W).qqqq[1]
#define qqqq_b2(W) (W).qqqq[2]
#define qqqq_b3(W) (W).qqqq[3]
#define hh_b0(W)   qqqq_b0((W))
#define hh_b1(W)   qqqq_b1((W))
#define hh_lh(W)   (W).hh[0]
#define hh_rh(W)   (W).hh[1]
// ~~~ End section 113 ~~~

// ~~~ Section 118 ~~~
#define link(X) hh_rh(mem[(X)]) // the |link| field of a memory word
#define info(X) hh_lh(mem[(X)]) // the |info| field of a memory word
// ~~~ End section 118 ~~~

// ~~~ Section 121 ~~~
// single-word node liberation
#ifdef STAT
#define decr_dyn_used decr(dyn_used)
#define incr_dyn_used incr(dyn_used)
#else
#define decr_dyn_used
#define incr_dyn_used
#endif

#define free_avail(X) link((X)) = avail; avail = (X); decr_dyn_used
// ~~~ End section 121 ~~~

// ~~~ Section 122 ~~~
#define fast_get_avail(X)                                 \
    do {                                                  \
        /* avoid |get avail| if possible, to save time */ \
        (X) = avail;                                      \
        if ((X) == null) {                                \
            (X) = get_avail();                            \
        }                                                 \
        else {                                            \
            avail = link((X));                            \
            link((X)) = null;                             \
            incr_dyn_used;                                \
        }                                                 \
    } while(0)
// ~~~ End section 122 ~~~

// ~~~ Section 124 ~~~
#define is_empty(X) (link((X)) == EMPTY_FLAG) // tests for empty node
#define node_size   info          // the size field in empty variable-size nodes
#define llink(X)    info((X) + 1) // left link in doubly-linked list of empty nodes
#define rlink(X)    link((X) + 1) // right link in doubly-linked list of empty nodes
// ~~~ End section 124 ~~~

// ~~~ Section 133 ~~~
#define type(X)    hh_b0(mem[(X)]) // identifies what kind of node this is
#define subtype(X) hh_b1(mem[(X)]) // secondary identification in some cases
// ~~~ End section 133 ~~~

// ~~~ Section 134 ~~~
#define is_char_node(X) ((X) >= hi_mem_min) // does the argument point to a |CHAR_NODE|?
#define font            type                // the font code in a |CHAR_NODE|
#define character       subtype             // the character code in a |CHAR_NODE|
// ~~~ End section 134 ~~~

// ~~~ Section 135 ~~~
#define width(X)        mem[(X) + WIDTH_OFFSET].sc  // width of the box, in sp
#define depth(X)        mem[(X) + DEPTH_OFFSET].sc  // depth of the box, in sp
#define height(X)       mem[(X) + HEIGHT_OFFSET].sc // height of the box, in sp
#define shift_amount(X) mem[(X) + 4].sc             // repositioning distance, in sp
#define list_ptr(X)     link((X) + LIST_OFFSET)     // beginning of the list inside the box
#define glue_order(X)   subtype((X) + LIST_OFFSET)  // applicable order of infinity
#define glue_sign(X)    type((X) + LIST_OFFSET)     // stretching or shrinking
#define glue_set(X)     mem[(X) + GLUE_OFFSET].gr   // a word of type |glue_ratio| for glue setting
// ~~~ End section 135 ~~~

// ~~~ Section 138 ~~~
#define is_running(X) ((X) == NULL_FLAG) // tests for a running dimension
// ~~~ End section 138 ~~~

// ~~~ Section 140 ~~~
#define float_cost(X)    mem[(X) + 1].integer // the |floating_penalty| to be used
#define ins_ptr(X)       info((X) + 4)        // the vertical list to be inserted
#define split_top_ptr(X) link((X) + 4)        // the |split_top_skip| to be used
// ~~~ End section 140 ~~~

// ~~~ Section 141 ~~~
#define mark_ptr(X) mem[(X) + 1].integer // head of the token list for a mark
// ~~~ End section 141 ~~~

// ~~~ Section 142 ~~~
#define adjust_ptr mark_ptr // vertical list to be moved out of horizontal list
// ~~~ End section 142 ~~~

// ~~~ Section 143 ~~~
#define lig_char(X) ((X) + 1)           // the word where the ligature is to be found
#define lig_ptr(X)  link(lig_char((X))) // the list of characters
// ~~~ End section 143 ~~~

// ~~~ Section 145 ~~~
#define replace_count subtype // how many subsequent nodes to replace
#define pre_break     llink   // text that precedes a discretionary break
#define post_break    rlink   // text that follows a discretionary break
// ~~~ End section 145 ~~~

// ~~~ Section 148 ~~~
#define precedes_break(X)  (type((X)) < MATH_NODE)
#define non_discardable(X) (type((X)) < MATH_NODE)
// ~~~ End section 148 ~~~

// ~~~ Section 149 ~~~
#define glue_ptr   llink // pointer to a glue specification
#define leader_ptr rlink // pointer to box or rule node for leaders
// ~~~ End section 149 ~~~

// ~~~ Section 150 ~~~
#define glue_ref_count(X) link((X))       // reference count of a glue specification
#define stretch(X)        mem[(X) + 2].sc // the stretchability of this glob of glue
#define shrink(X)         mem[(X) + 3].sc // the shrinkability of this glob of glue
#define stretch_order     type            // order of infinity for stretching
#define shrink_order      subtype         // order of infinity for shrinking
// ~~~ End section 150 ~~~

// ~~~ Section 157 ~~~
#define penalty(X) mem[(X) + 1].integer // the added cost of breaking a list here
// ~~~ End section 157 ~~~

// ~~~ Section 159 ~~~
#define glue_stretch(X) mem[(X) + GLUE_OFFSET].sc // total stretch in an unset node
#define glue_shrink     shift_amount              // total shrink in an unset node
#define span_count      subtype                   // indicates the number of spanned columns
// ~~~ End section 159 ~~~

// ~~~ Section 200 ~~~
#define token_ref_count(X) info((X)) // reference count preceding a token list
// ~~~ End section 200 ~~~

// ~~~ Section 201 ~~~
#define fast_delete_glue_ref(X)             \
    do {                                    \
        if (glue_ref_count((X)) == null) {  \
            free_node((X), GLUE_SPEC_SIZE); \
        }                                   \
        else {                              \
            decr(glue_ref_count((X)));      \
        }                                   \
    } while (0)
// ~~~ End section 201 ~~~

// ~~~ Section 203 ~~~
#define add_token_ref(X) incr(token_ref_count((X))) // new reference to a token list
#define add_glue_ref(X)  incr(glue_ref_count((X)))  // new reference to a glue spec
// ~~~ End section 203 ~~~

// ~~~ Section 213 ~~~
#define mode            cur_list.mode_field // current mode
#define head            cur_list.head_field // header node of current list
#define tail            cur_list.tail_field // final node on current list
#define prev_graf       cur_list.pg_field   // number of paragraph lines accumulated
#define aux             cur_list.aux_field  // auxiliary data about the current list
#define prev_depth      aux.sc              // the name of |aux| in vertical mode
#define space_factor    hh_lh(aux)          // part of |aux| in horizontal mode
#define clang           hh_rh(aux)          // the other part of |aux| in horizontal mode
#define incompleat_noad aux.integer         // the name of |aux| in math mode
#define mode_line       cur_list.ml_field   // source file line number at beginning of list
// ~~~ End section 213 ~~~

// ~~~ Section 214 ~~~
#define tail_append(X) link(tail) = (X); tail = link(tail)
// ~~~ End section 214 ~~~

// ~~~ Section 221 ~~~
#define eq_level_field(X) hh_b1((X))
#define eq_type_field(X)  hh_b0((X))
#define equiv_field(X)    hh_rh((X))

#define eq_level(X) eq_level_field(eqtb[(X)]) // level of definition
#define eq_type(X)  eq_type_field(eqtb[(X)])  // command code for equivalent
#define equiv(X)    equiv_field(eqtb[(X)])    // equivalent value
// ~~~ End section 221 ~~~

// ~~~ Section 224 ~~~
#define skip(X)     equiv(SKIP_BASE + (X))    // |mem| location of glue specification
#define mu_skip(X)  equiv(MU_SKIP_BASE + (X)) // |mem| location of math glue spec
#define glue_par(X) equiv(GLUE_BASE + (X))    // |mem| location of glue specification

#define line_skip                glue_par(LINE_SKIP_CODE)
#define baseline_skip            glue_par(BASELINE_SKIP_CODE)
#define par_skip                 glue_par(PAR_SKIP_CODE)
#define above_display_skip       glue_par(ABOVE_DISPLAY_SKIP_CODE)
#define below_display_skip       glue_par(BELOW_DISPLAY_SKIP_CODE)
#define above_display_short_skip glue_par(ABOVE_DISPLAY_SHORT_SKIP_CODE)
#define below_display_short_skip glue_par(BELOW_DISPLAY_SHORT_SKIP_CODE)
#define left_skip                glue_par(LEFT_SKIP_CODE)
#define right_skip               glue_par(RIGHT_SKIP_CODE)
#define top_skip                 glue_par(TOP_SKIP_CODE)
#define split_top_skip           glue_par(SPLIT_TOP_SKIP_CODE)
#define tab_skip                 glue_par(TAB_SKIP_CODE)
#define space_skip               glue_par(SPACE_SKIP_CODE)
#define xspace_skip              glue_par(XSPACE_SKIP_CODE)
#define par_fill_skip            glue_par(PAR_FILL_SKIP_CODE)
#define thin_mu_skip             glue_par(THIN_MU_SKIP_CODE)
#define med_mu_skip              glue_par(MED_MU_SKIP_CODE)
#define thick_mu_skip            glue_par(THICK_MU_SKIP_CODE)
// ~~~ End section 224 ~~~

// ~~~ Section 230 ~~~
#define par_shape_ptr  equiv(PAR_SHAPE_LOC)
#define output_routine equiv(OUTPUT_ROUTINE_LOC)
#define every_par      equiv(EVERY_PAR_LOC)
#define every_math     equiv(EVERY_MATH_LOC)
#define every_display  equiv(EVERY_DISPLAY_LOC)
#define every_hbox     equiv(EVERY_HBOX_LOC)
#define every_vbox     equiv(EVERY_VBOX_LOC)
#define every_job      equiv(EVERY_JOB_LOC)
#define every_cr       equiv(EVERY_CR_LOC)
#define err_help       equiv(ERR_HELP_LOC)
#define toks(X)        equiv(TOKS_BASE + (X))
#define box(X)         equiv(BOX_BASE + (X))
#define cur_font       equiv(CUR_FONT_LOC)
#define fam_fnt(X)     equiv(MATH_FONT_BASE + (X))
#define cat_code(X)    equiv(CAT_CODE_BASE + (X))
#define lc_code(X)     equiv(LC_CODE_BASE + (X))
#define uc_code(X)     equiv(UC_CODE_BASE + (X))
#define sf_code(X)     equiv(SF_CODE_BASE + (X))
// Note: |math_code(c)| is the true math code plus |MIN_HALFWORD|
#define math_code(X)   equiv(MATH_CODE_BASE + (X))
// ~~~ End section 230 ~~~

// ~~~ Section 236 ~~~
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
// ~~~ End section 236 ~~~

// ~~~ Section 247 ~~~
#define dimen(X)             eqtb[SCALED_BASE + (X)].sc
#define dimen_par(X)         eqtb[DIMEN_BASE + (X)].sc  // a scaled quantity
#define par_indent           dimen_par(PAR_INDENT_CODE)
#define math_surround        dimen_par(MATH_SURROUND_CODE)
#define line_skip_limit      dimen_par(LINE_SKIP_LIMIT_CODE)
#define hsize                dimen_par(HSIZE_CODE)
#define vsize                dimen_par(VSIZE_CODE)
#define max_depth            dimen_par(MAX_DEPTH_CODE)
#define split_max_depth      dimen_par(SPLIT_MAX_DEPTH_CODE)
#define box_max_depth        dimen_par(BOX_MAX_DEPTH_CODE)
#define hfuzz                dimen_par(HFUZZ_CODE)
#define vfuzz                dimen_par(VFUZZ_CODE)
#define delimiter_shortfall  dimen_par(DELIMITER_SHORTFALL_CODE)
#define null_delimiter_space dimen_par(NULL_DELIMITER_SPACE_CODE)
#define script_space         dimen_par(SCRIPT_SPACE_CODE)
#define pre_display_size     dimen_par(PRE_DISPLAY_SIZE_CODE)
#define display_width        dimen_par(DISPLAY_WIDTH_CODE)
#define display_indent       dimen_par(DISPLAY_INDENT_CODE)
#define overfull_rule        dimen_par(OVERFULL_RULE_CODE)
#define hang_indent          dimen_par(HANG_INDENT_CODE)
#define h_offset             dimen_par(H_OFFSET_CODE)
#define v_offset             dimen_par(V_OFFSET_CODE)
#define emergency_stretch    dimen_par(EMERGENCY_STRETCH_CODE)
// ~~~ End section 247 ~~~

// ~~~ Section 256 ~~~
#define next(X)         hh_lh(hash[(X)]) // link for coalesced lists
#define text(X)         hh_rh(hash[(X)]) // string number for control sequence name
#define hash_is_full    (hash_used == HASH_BASE) // test if all positions are occupied
#define font_id_text(X) text(FONT_ID_BASE + (X)) // a frozen font identifier's name
// ~~~ End section 256 ~~~

// ~~~ Section 268 ~~~
#define save_type(X)  hh_b0(save_stack[(X)]) // classifies a |save_stack| entry
#define save_level(X) hh_b1(save_stack[(X)]) // saved level for regions 5 and 6, or group code
#define save_index(X) hh_rh(save_stack[(X)]) // |eqtb| location or token or |save_stack| location
// ~~~ End section 268 ~~~

// ~~~ Section 273 ~~~
#define check_full_save_stack                     \
    do {                                          \
        if (save_ptr > max_save_stack) {          \
            max_save_stack = save_ptr;            \
            if (max_save_stack > SAVE_SIZE - 6) { \
                overflow("save size", SAVE_SIZE); \
            }                                     \
        }                                         \
    } while (0)
// ~~~ End section 273 ~~~

// ~~~ Section 274 ~~~
#define saved(X) save_stack[save_ptr + (X)].integer
// ~~~ End section 274 ~~~

// ~~~ Section 302 ~~~
#define state cur_input.state_field // current scanner state
#define index cur_input.index_field // reference for buffer information
#define start cur_input.start_field // starting position in |buffer|
#define limit cur_input.limit_field // end of current line in |buffer|
#define name  cur_input.name_field  // name of the current file
// ~~~ End section 302 ~~~

// ~~~ Section 304 ~~~
#define terminal_input (name == 0)       // are we reading from the terminal?
#define cur_file       input_file[index] // the current |alpha_file| variable
// ~~~ End section 304 ~~~

// ~~~ Section 307 ~~~
#define token_type  index // type of current token list
#define param_start limit // base of macro parameters in |param_stack|
// ~~~ End section 307 ~~~

// ~~~ Section 321 ~~~
// enter a new input level, save the old
#define push_input                                             \
    if (input_ptr > max_in_stack) {                            \
        max_in_stack = input_ptr;                              \
        if (input_ptr == STACK_SIZE) {                         \
            overflow("input stack size", STACK_SIZE);          \
        }                                                      \
    }                                                          \
    input_stack[input_ptr] = cur_input; /* stack the record */ \
    incr(input_ptr)
// ~~~ End section 321 ~~~

// ~~~ Section 322 ~~~
// leave an input level, re-enter the old
#define pop_input                      \
    decr(input_ptr);                   \
    cur_input = input_stack[input_ptr]
// ~~~ End section 322 ~~~

// ~~~ Section 323 ~~~
#define back_list(X) begin_token_list((X), BACKED_UP) // backs up a simple token list
#define ins_list(X)  begin_token_list((X), INSERTED)  // inserts a simple token list
// ~~~ End section 323 ~~~

// ~~~ Section 1381 ~~~
// single-word node allocation
pointer get_avail();

// makes list of single-word nodes
void flush_list(pointer p);

// variable-size node allocation
pointer get_node(int s);

// variable-size node liberation
void free_node(pointer p, halfword s);

#ifdef INIT
// sorts the available variable-size nodes by location
void sort_avail();
#endif

#ifdef DEBUG
void check_mem(bool print_locs);
// look for pointers to |p|
void search_mem(pointer p);
#endif

// creates a new box node
pointer new_null_box();

pointer new_rule();

pointer new_ligature(quarterword f, quarterword c, pointer q);
pointer new_lig_item(quarterword c);

pointer new_disc();

pointer new_math(scaled w, small_number s);

// duplicates a glue specification
pointer new_spec(pointer p);

pointer new_param_glue(small_number n);

pointer new_glue(halfword q);

pointer new_skip_param(small_number n);

pointer new_kern(scaled w);

pointer new_penalty(int m);

// |p| points to the reference count of a token list that is losing one reference
void delete_token_ref(pointer p);

// |p| points to a glue specification
void delete_glue_ref(pointer p);

// erase list of nodes starting at |p|
void flush_node_list(pointer p);

// makes a duplicate of the node list that starts at |p|
// and returns a pointer to the new list
pointer copy_node_list(pointer p);

// enter a new semantic level, save the old
void push_nest();

// leave a semantic level, re-enter the old
void pop_nest();

// search the hash table
pointer id_lookup(int j, int l);

#ifdef INIT
void primitive(char *s, quarterword c, halfword o);
#endif

// begin a new level of grouping
void new_save_level(int c);

//  new data for |eqtb|
void eq_define(pointer p, quarterword t, halfword e);

void eq_word_define(pointer p, int w);

// global |eq_define|
void geq_define(pointer p, quarterword t, halfword e);

// global |eq_word_define|
void geq_word_define(pointer p, int w);

void save_for_after(halfword t);

// pops the top level off the save stack
void unsave();

void prepare_mag();

void runaway();

void begin_token_list(pointer p, quarterword t);

// leave a token-list input level
void end_token_list();

// undoes one token of input
void back_input();

// back up one token and call |error|
void back_error();

// back up one inserted token and call |error|
void ins_error();

void begin_file_reading();

void end_file_reading();

#endif
// ~~~ End section 1381 ~~~
