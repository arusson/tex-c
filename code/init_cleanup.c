// ~~~ Section 4 ~~~
// ~~~ Start file |init_cleanup.c|, 1382 ~~~
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "builder.h"
#include "conditional.h"
#include "dvi.h"
#include "texerror.h"
#include "parser.h"
#ifdef INIT
#include "breaker.h"
#endif
// ~~~ End section 1382 ~~~

void initialize() {
    // ~~~ Local variables for initialization, 19 ~~~
    // int i; no used
    
    // ~~~ Section 163 ~~~
    int k; // index into |mem|, |eqtb|, etc
    // ~~~ End section 163 ~~~
    
    // ~~~ Section 927 ~~~
    int z; // runs through the exception dictionary
    // ~~~ End section 927 ~~~
    // ~~~ End section 19 ~~~
    // ~~~ Initialize whatever TeX might access, 8 ~~~
    // ~~~ Set initial values of key variables, 21 ~~~
    
    // ~~~ Section 74 ~~~
    interaction = ERROR_STOP_MODE;
    // ~~~ End section 74 ~~~
    
    // ~~~ Section 77 ~~~
    deletions_allowed = true;
    set_box_allowed = true;
    error_count = 0;
    // history is initialized elsewhere
    // ~~~ End section 77 ~~~
    
    // ~~~ Section 80 ~~~
    help_ptr = 0;
    use_err_help = false;
    // ~~~ End section 80 ~~~
    
    // ~~~ Section 97 ~~~
    interrupt = 0;
    ok_to_interrupt = true;
    // ~~~ End section 97 ~~~
    
    // ~~~ Section 166 ~~~
#ifdef DEBUG
    was_mem_end = MEM_MIN; // indicate that everything was previously free
    was_lo_max = MEM_MIN;
    was_hi_min = MEM_MAX;
    panicking = false;
#endif
    // ~~~ End section 166 ~~~
    
    // ~~~ Section 215 ~~~
    nest_ptr = 0;
    max_nest_stack = 0;
    mode = VMODE;
    head = CONTRIB_HEAD;
    tail = CONTRIB_HEAD;
    prev_depth = IGNORE_DEPTH;
    mode_line = 0;
    prev_graf = 0;
    shown_mode = 0;
    // ~~~ Start a new current page, 991 ~~~
    page_contents = EMPTY;
    page_tail = PAGE_HEAD;
    link(PAGE_HEAD) = null;
    last_glue = MAX_HALFWORD;
    last_penalty = 0;
    last_kern = 0;
    page_depth = 0;
    page_max_depth = 0;
    // ~~~ End section 991 ~~~
    // ~~~ End section 215 ~~~
    
    // ~~~ Section 254 ~~~
    for(k = INT_BASE; k <= EQTB_SIZE; k++) {
        xeq_level[k] = LEVEL_ONE;
    }
    // ~~~ End section 254 ~~~
    
    // ~~~ Section 257 ~~~
    no_new_control_sequence = true; // new identifiers are usually forbidden
    next(HASH_BASE) = 0;
    text(HASH_BASE) = 0;
    for(k = HASH_BASE + 1;  k < UNDEFINED_CONTROL_SEQUENCE; k++) {
        hash[k] = hash[HASH_BASE];
    }
    // ~~~ End section 257 ~~~
    
    // ~~~ Section 272 ~~~
    save_ptr = 0;
    cur_level = LEVEL_ONE;
    cur_group = BOTTOM_LEVEL;
    cur_boundary = 0;
    max_save_stack = 0;
    // ~~~ End section 272 ~~~
    
    // ~~~ Section 287 ~~~
    mag_set = 0;
    // ~~~ End section 287 ~~~
    
    // ~~~ Section 383 ~~~
    top_mark = null;
    first_mark = null;
    bot_mark = null;
    split_first_mark = null;
    split_bot_mark = null;
    // ~~~ End section 383 ~~~
    
    // ~~~ Section 439 ~~~
    cur_val = 0;
    cur_val_level = INT_VAL;
    radix = 0;
    cur_order = NORMAL;
    // ~~~ End section 439 ~~~
    
    // ~~~ Section 481 ~~~
    for(k = 0; k <= 16; k++) {
        read_open[k] = CLOSED;
    }
    // ~~~ End section 481 ~~~
    
    // ~~~ Section 490 ~~~
    cond_ptr = null;
    if_limit = NORMAL;
    cur_if = 0;
    if_line = 0;
    // ~~~ End section 490 ~~~
    
    // ~~~ Section 521 ~~~
    memcpy(tex_format_default, "TeXformats/plain.fmt", 20);
    // ~~~ End section 521 ~~~
    
    // ~~~ Section 551 ~~~
    for(k = FONT_BASE; k <= FONT_MAX; k++) {
        font_used[k] = false;
    }
    // ~~~ End section 551 ~~~
    
    // ~~~ Section 556 ~~~
    qqqq_b0(null_character) = MIN_QUARTERWORD;
    qqqq_b1(null_character) = MIN_QUARTERWORD;
    qqqq_b2(null_character) = MIN_QUARTERWORD;
    qqqq_b3(null_character) = MIN_QUARTERWORD;
    // ~~~ End section 556 ~~~
    
    // ~~~ Section 593 ~~~
    total_pages = 0;
    max_v = 0;
    max_h = 0;
    max_push = 0;
    last_bop = -1;
    doing_leaders = false;
    dead_cycles = 0;
    cur_s = -1;
    // ~~~ End section 593 ~~~
    
    // ~~~ Section 596 ~~~
    half_buf = DVI_BUF_SIZE / 2;
    dvi_limit = DVI_BUF_SIZE;
    dvi_ptr = 0;
    dvi_offset = 0;
    dvi_gone = 0;
    // ~~~ End section 596 ~~~
    
    // ~~~ Section 606 ~~~
    down_ptr = null;
    right_ptr = null;
    // ~~~ End section 606 ~~~
    
    // ~~~ Section 648 ~~~
    adjust_tail = null;
    last_badness = 0;
    // ~~~ End section 648 ~~~
    
    // ~~~ Section 662 ~~~
    pack_begin_line = 0;
    // ~~~ End section 662 ~~~
    
    // ~~~ Section 685 ~~~
    hh_rh(empty_field) = EMPTY;
    hh_lh(empty_field) = null;
    qqqq_b0(null_delimiter) = 0;
    qqqq_b1(null_delimiter) = MIN_QUARTERWORD;
    qqqq_b2(null_delimiter) = 0;
    qqqq_b3(null_delimiter) = MIN_QUARTERWORD;
    // ~~~ End section 685 ~~~
    
    // ~~~ Section 771 ~~~
    align_ptr = null;
    cur_align = null;
    cur_span = null;
    cur_loop = null;
    cur_head = null;
    cur_tail = null;
    // ~~~ End section 771 ~~~
    
    // ~~~ Section 928 ~~~
    for(z = 0; z <= HYPH_SIZE; z++) {
        hyph_word[z] = 0;
        hyph_list[z] = null;
    }
    hyph_count = 0;
    // ~~~ End section 928 ~~~
    
    // ~~~ Section 990 ~~~
    output_active = false;
    insert_penalties = 0;
    // ~~~ End section 990 ~~~
    
    // ~~~ Section 1033 ~~~
    ligature_present = false;
    cancel_boundary = false;
    lft_hit = false;
    rt_hit = false;
    ins_disc = false;
    // ~~~ End section 1033 ~~~
    
    // ~~~ Section 1267 ~~~
    after_token = 0;
    // ~~~ End section 1267 ~~~
    
    // ~~~ Section 1282 ~~~
    long_help_seen = false;
    // ~~~ End section 1282 ~~~
    
    // ~~~ Section 1300 ~~~
    format_ident = 0;
    // ~~~ End section 1300 ~~~
    
    // ~~~ Section 1343 ~~~
    for(k = 0; k <= 17; k++) {
        write_open[k] = false;
    }
    // ~~~ End section 1343 ~~~
    // ~~~ End section 21 ~~~
#ifdef INIT
    // ~~~ Initialize table entries (done by INITEX only), 164 ~~~
    for(k = MEM_BOT + 1; k <= LO_MEM_STAT_MAX; k++) {
        mem[k].sc = 0; // all glue dimensions are zeroed
    }
    k = MEM_BOT;
    while (k <= LO_MEM_STAT_MAX) {
        // set first words of glue specifications
        glue_ref_count(k) = null + 1;
        stretch_order(k) = NORMAL;
        shrink_order(k) = NORMAL;
        k += GLUE_SPEC_SIZE;
    }
    
    stretch(FIL_GLUE) = UNITY;
    stretch_order(FIL_GLUE) = FIL;
    
    stretch(FILL_GLUE) = UNITY;
    stretch_order(FILL_GLUE) = FILL;
    
    stretch(SS_GLUE) = UNITY;
    stretch_order(SS_GLUE) = FIL;
    
    shrink(SS_GLUE) = UNITY;
    shrink_order(SS_GLUE) = FIL;
    
    stretch(FIL_NEG_GLUE) = -UNITY;
    stretch_order(FIL_NEG_GLUE) = FIL;
    
    // now initialize the dynamic memory
    rover = LO_MEM_STAT_MAX + 1;
    link(rover) = EMPTY_FLAG;
    // which is a 1000-word available node
    node_size(rover) = 1000;
    llink(rover) = rover;
    rlink(rover) = rover;
    lo_mem_max = rover + 1000;
    link(lo_mem_max) = null;
    info(lo_mem_max) = null;
    
    for(k = HI_MEM_STAT_MIN; k <= MEM_TOP; k++) {
        mem[k] = mem[lo_mem_max]; // clear list heads
    }
    
    // ~~~ Initialize the special list heads and constant nodes, 790 ~~~
    info(OMIT_TEMPLATE) = END_TEMPLATE_TOKEN; // |link(OMIT_TEMPLATE) = null|
    
    // ~~~ Section 797 ~~~
    link(END_SPAN) = MAX_QUARTERWORD + 1;
    info(END_SPAN) = null;
    // ~~~ End section 797 ~~~
    
    // ~~~ Section 820 ~~~
    type(LAST_ACTIVE) = HYPHENATED;
    line_number(LAST_ACTIVE) = MAX_HALFWORD;
    subtype(LAST_ACTIVE) = 0; // the |subtype| is never examined by the algorithm
    // ~~~ End section 820 ~~~
    
    // ~~~ Section 981 ~~~
    subtype(PAGE_INS_HEAD) = 255;
    type(PAGE_INS_HEAD) = SPLIT_UP;
    link(PAGE_INS_HEAD) = PAGE_INS_HEAD;
    // ~~~ End section 981 ~~~
    
    // ~~~ Section 988 ~~~
    type(PAGE_HEAD) = GLUE_NODE;
    subtype(PAGE_HEAD) = NORMAL;
    // ~~~ End section 988 ~~~
    // ~~~ End section 790 ~~~
    
    // initialize the one-word memory
    avail = null;
    mem_end = MEM_TOP;
    hi_mem_min = HI_MEM_STAT_MIN;
    // initialize statistics
    var_used = LO_MEM_STAT_MAX + 1 - MEM_BOT;
    dyn_used = HI_MEM_STAT_USAGE;
    
    // ~~~ Section 222 ~~~
    eq_type(UNDEFINED_CONTROL_SEQUENCE) = UNDEFINED_CS;
    equiv(UNDEFINED_CONTROL_SEQUENCE) = null;
    eq_level(UNDEFINED_CONTROL_SEQUENCE) = LEVEL_ZERO;
    for(k = ACTIVE_BASE; k < UNDEFINED_CONTROL_SEQUENCE; k++) {
        eqtb[k] = eqtb[UNDEFINED_CONTROL_SEQUENCE];
    }
    // ~~~ End section 222 ~~~
    
    // ~~~ Section 228 ~~~
    equiv(GLUE_BASE) = ZERO_GLUE;
    eq_level(GLUE_BASE) = LEVEL_ONE;
    eq_type(GLUE_BASE) = GLUE_REF;
    for(k = GLUE_BASE + 1; k < LOCAL_BASE; k++) {
        eqtb[k] = eqtb[GLUE_BASE];
    }
    glue_ref_count(ZERO_GLUE) += LOCAL_BASE - GLUE_BASE;
    // ~~~ End section 228 ~~~
    
    // ~~~ Section 232 ~~~
    par_shape_ptr = null;
    eq_type(PAR_SHAPE_LOC) = SHAPE_REF;
    eq_level(PAR_SHAPE_LOC) = LEVEL_ONE;
    for(k = OUTPUT_ROUTINE_LOC; k <= TOKS_BASE + 255; k++) {
        eqtb[k] = eqtb[UNDEFINED_CONTROL_SEQUENCE];
    }
    box(0) = null;
    eq_type(BOX_BASE) = BOX_REF;
    eq_level(BOX_BASE) = LEVEL_ONE;
    for(k = BOX_BASE + 1; k <= BOX_BASE + 255; k++) {
        eqtb[k] = eqtb[BOX_BASE];
    }
    cur_font = NULL_FONT;
    eq_type(CUR_FONT_LOC) = DATA;
    eq_level(CUR_FONT_LOC) = LEVEL_ONE;
    for(k = MATH_FONT_BASE; k <= MATH_FONT_BASE + 47; k++) {
        eqtb[k] = eqtb[CUR_FONT_LOC];
    }
    equiv(CAT_CODE_BASE) = 0;
    eq_type(CAT_CODE_BASE) = DATA;
    eq_level(CAT_CODE_BASE) = LEVEL_ONE;
    for(k = CAT_CODE_BASE + 1; k <= INT_BASE - 1; k++) {
        eqtb[k] = eqtb[CAT_CODE_BASE];
    }
    for(k = 0; k <= 255; k++) {
        cat_code(k) = OTHER_CHAR;
        math_code(k) = hi(k);
        sf_code(k) = 1000;
    }
    cat_code(CARRIAGE_RETURN) = CAR_RET;
    cat_code(' ') = SPACER;
    cat_code('\\') = ESCAPE;
    cat_code('%') = COMMENT;
    cat_code(INVALID_CODE) = INVALID_CHAR;
    cat_code(NULL_CODE) = IGNORE;
    for(k = '0'; k <= '9'; k++) {
        math_code(k) = hi(k + VAR_CODE);
    }
    for(k = 'A'; k <= 'Z'; k++) {
        cat_code(k) = LETTER;
        cat_code(k + 'a' - 'A') = LETTER;
        math_code(k) = hi(k + VAR_CODE + 0x100);
        math_code(k + 'a' - 'A') = hi(k + 'a' - 'A' + VAR_CODE + 0x100);
        lc_code(k) = k + 'a' - 'A';
        lc_code(k + 'a' - 'A') = k + 'a' - 'A';
        uc_code(k) = k;
        uc_code(k + 'a' - 'A') = k;
        sf_code(k) = 999;
    }
    // ~~~ End section 232 ~~~
    
    // ~~~ Section 240 ~~~
    for(k = INT_BASE; k < DEL_CODE_BASE; k++) {
        eqtb[k].integer = 0;
    }
    mag = 1000;
    tolerance = 10000;
    hang_after = 1; max_dead_cycles = 25;
    escape_char = '\\';
    end_line_char = CARRIAGE_RETURN;
    for(k = 0; k <= 255; k++) {
        del_code(k) = -1;
    }
    del_code('.') = 0; // this null delimiter is used in error recovery
    // ~~~ End section 240 ~~~
    
    // ~~~ Section 250 ~~~
    for(k = DIMEN_BASE; k <= EQTB_SIZE; k++) {
        eqtb[k].sc = 0;
    }
    // ~~~ End section 250 ~~~
    
    // ~~~ Section 258 ~~~
    hash_used = FROZEN_CONTROL_SEQUENCE; // nothing is used
    cs_count = 0;
    eq_type(FROZEN_DONT_EXPAND) = DONT_EXPAND;
    text(FROZEN_DONT_EXPAND) = NOTEXPANDED_STRING;
    // ~~~ End section 258 ~~~
    
    // ~~~ Section 552 ~~~
    font_ptr = NULL_FONT;
    fmem_ptr = 7;
    font_name[NULL_FONT] = NULLFONT_STRING;
    font_area[NULL_FONT] = EMPTY_STRING;
    hyphen_char[NULL_FONT] = '-';
    skew_char[NULL_FONT] = -1;
    bchar_label[NULL_FONT] = NON_ADDRESS;
    font_bchar[NULL_FONT] = NON_CHAR;
    font_false_bchar[NULL_FONT] = NON_CHAR;
    font_bc[NULL_FONT] = 1;
    font_ec[NULL_FONT] = 0;
    font_size[NULL_FONT] = 0;
    font_dsize[NULL_FONT] = 0;
    char_base[NULL_FONT] = 0;
    width_base[NULL_FONT] = 0;
    height_base[NULL_FONT] = 0;
    depth_base[NULL_FONT] = 0;
    italic_base[NULL_FONT] = 0;
    lig_kern_base[NULL_FONT] = 0;
    kern_base[NULL_FONT] = 0;
    exten_base[NULL_FONT] = 0;
    font_glue[NULL_FONT] = null;
    font_params[NULL_FONT] = 7;
    param_base[NULL_FONT] = -1;
    for(k = 0; k <= 6; k++) {
        font_info[k].sc = 0;
    }
    // ~~~ End section 552 ~~~
    
    // ~~~ Section 946 ~~~
    for(k = -TRIE_OP_SIZE; k <= TRIE_OP_SIZE; k++) {
        trie_op_hash[k] = 0;
    }
    for(k = 0; k <= 255; k++) {
        trie_used[k] = MIN_QUARTERWORD;
    }
    trie_op_ptr = 0;
    // ~~~ End section 946 ~~~
    
    // ~~~ Section 951 ~~~
    trie_not_ready = true;
    trie_root = 0;
    trie_c[0] = 0;
    trie_ptr = 0;
    // ~~~ End section 951 ~~~
    
    // ~~~ Section 1216 ~~~
    text(FROZEN_PROTECTION) = INACCESSIBLE_STRING;
    // ~~~ End section 1216 ~~~
    
    // ~~~ Section 1301 ~~~
    format_ident = INITEX_IDENT_STRING; // " (INITEX)"
    // ~~~ End section 1301 ~~~
    
    // ~~~ Section 1369 ~~~
    text(END_WRITE) = ENDWRITE_STRING; // "endwrite"
    eq_level(END_WRITE) = LEVEL_ONE;
    eq_type(END_WRITE) = OUTER_CALL;
    equiv(END_WRITE) = null;
    // ~~~ End section 1369 ~~~
    // ~~~ End section 164 ~~~
#endif
    // ~~~ End section 8 ~~~
}
// ~~~ End section 4 ~~~

// ~~~ Section 37 ~~~
// gets the terminal input started
bool init_terminal(int argc, char *argv[]) {
    int last_nonblank; // |last| with trailing blanks removed
    int i; // index into |argv|
    int j; // indox into an argument of |argv|
    int n; // length of an argument

    // The code below does the same thing as |input_ln|
    last = first;
    last_nonblank = first;
    for(i = 1; i < argc; i++) {
        n = strlen(argv[i]);
        if (last >= max_buf_stack) {
            max_buf_stack = last + n + 1; // a single space is added between arguments
            if (max_buf_stack >= BUF_SIZE) {
                // ~~~ Report overflow of the input buffer, and abort, 35 ~~~
                if (format_ident == 0) {
                    printf("Buffer size exceeded!\n");
                    exit(0); // Goto final_end
                }
                else {
                    cur_input.loc_field = first;
                    cur_input.limit_field = last - 1;
                    overflow("buffer size", BUF_SIZE);
                }
                // ~~~ End section 35 ~~~
            }
        }
        for(j = 0; j < n; j++) {
            buffer[last] = XORD[(int)argv[i][j]];
            incr(last);
            if (buffer[last - 1] != ' ') {
                last_nonblank = last;
            }
        }
        buffer[last] = ' ';
        incr(last);
    }
    last = last_nonblank;
    
    // the (adapted) original loop
    while (true) {
        loc = first;
        while (loc < last && buffer[loc] == ' ') {
            incr(loc);
        }
        if (loc < last) {
            return true;
        }
        printf("Please type the name of your input file.\n");
        printf("**");
        update_terminal;
        if (!input_ln(stdin)) {
            // this should'nt happen
            printf("\n!End of file on the terminal... why?");
            return false;
        }
    }
}
// ~~~ End section 37 ~~~

// ~~~ Section 241 ~~~
void fix_date_and_time() {
    time_t rawtime;
    struct tm *data;
    time(&rawtime);
    data = localtime(&rawtime);
    sys_time = data->tm_hour * 60 + data->tm_min;
    sys_day = data->tm_mday;
    sys_month = data->tm_mon + 1;
    sys_year = data->tm_year + 1900;

    time_ = sys_time;  // minutes since midnight
    day = sys_day;     // day of the month
    month = sys_month; // month of the year
    year = sys_year;   // Anno Domini
}
// ~~~ End section 241 ~~~

// ~~~ Section 1330 ~~~
// ~~~ Last-minute procedures, 1333 ~~~
void close_files_and_terminate() {
    int k; // all-purpose index
    // ~~~ Finish the extensions, 1378 ~~~
    for(k = 0; k <= 15; k++) {
        if (write_open[k]) {
            a_close(write_file[k]);
        }
    }
    // ~~~ End section 1378 ~~~
    new_line_char = -1;
#ifdef STAT
    if (tracing_stats > 0) {
        // ~~~ Output statistics about this job, 1334 ~~~
        if (log_opened) {
            wlog_ln(" ");
            wlog_ln("Here is how much of TeX's memory you used:");
            wlog(" %d string", str_ptr - init_str_ptr);
            if (str_ptr != init_str_ptr + 1) {
                wlog_char('s');
            }
            wlog_ln(" out of %d", MAX_STRINGS - init_str_ptr);
            wlog_ln(" %d string characters out of %d", pool_ptr - init_pool_ptr, POOL_SIZE - init_pool_ptr);
            wlog_ln(
                " %d words of memory out of %d",
                lo_mem_max - MEM_MIN + mem_end - hi_mem_min + 2,
                mem_end + 1 - MEM_MIN
            );
            wlog_ln(
                " %d multiletter control sequences out of %d",
                cs_count, HASH_SIZE
            );
            wlog(
                " %d words of font info for %d font",
                fmem_ptr, font_ptr - FONT_BASE
            );
            if (font_ptr != FONT_BASE + 1) {
                wlog_char('s');
            }
            wlog_ln(", out of %d for %d", FONT_MEM_SIZE, FONT_MAX - FONT_BASE);
            wlog(" %d hyphenation exception", hyph_count);
            if (hyph_count != 1) {
                wlog_char('s');
            }
            wlog_ln(" out of %d", HYPH_SIZE);
            wlog_ln(
                " %di,%dn,%dp,%db,%ds stack positions out of %di,%dn,%dp,%db,%ds", 
                max_in_stack,
                max_nest_stack,
                max_param_stack,
                max_buf_stack,
                max_save_stack + 6,
                STACK_SIZE,
                NEST_SIZE,
                PARAM_SIZE,
                BUF_SIZE,
                SAVE_SIZE
            );
        }
        // ~~~ End section 1334 ~~~
    }
#endif
    // ~~~ Finish the DVI file, 642 ~~~
    while (cur_s > -1) {
        if (cur_s > 0) {
            dvi_out(POP);
        }
        else {
            dvi_out(EOP);
            incr(total_pages);
        }
        decr(cur_s);
    }
    if (total_pages == 0) {
        print_nl("No pages of output.");
    }
    else {
        dvi_out(POST); // beginning of the postamble
        dvi_four(last_bop);
        last_bop = dvi_offset + dvi_ptr - 5; // |POST| location
        dvi_four(25400000);
        dvi_four(473628672); // conversion ratio for sp
        prepare_mag();
        dvi_four(mag); // magnification factor
        dvi_four(max_v);
        dvi_four(max_h);
        dvi_out(max_push / 256);
        dvi_out(max_push % 256);
        dvi_out((total_pages / 256) % 256);
        dvi_out(total_pages % 256);
        // ~~~ Output the font definitions for all fonts that were used, 643 ~~~
        while (font_ptr > FONT_BASE) {
            if (font_used[font_ptr]) {
                dvi_font_def(font_ptr);
            }
            decr(font_ptr);
        }
        // ~~~ End section 643 ~~~
        dvi_out(POST_POST);
        dvi_four(last_bop);
        dvi_out(ID_BYTE);
        k = 4 + ((DVI_BUF_SIZE - dvi_ptr) % 4); // the number of 223's
        while (k > 0) {
            dvi_out(223);
            decr(k);
        }
        // ~~~ Empty the last bytes out of |dvi_buf|, 599 ~~~
        if (dvi_limit == half_buf) {
            write_dvi(half_buf, DVI_BUF_SIZE - 1);
        }
        if (dvi_ptr > 0) {
            write_dvi(0, dvi_ptr - 1);
        }
        // ~~~ End section 599 ~~~
        print_nl("Output written on ");
        slow_print(output_file_name);
        print(" (");
        print_int(total_pages);
        print(" page");
        if (total_pages != 1) {
            print_char('s');
        }
        print(", ");
        print_int(dvi_offset + dvi_ptr);
        print(" bytes).");
        b_close(dvi_file);
    }
    // ~~~ End section 642 ~~~
    if (log_opened) {
        wlog_cr;
        a_close(log_file);
        selector -= 2;
        if (selector == TERM_ONLY) {
            print_nl("Transcript written on ");
            slow_print(log_name);
            print_char('.');
            print_ln();
        }
    }
}

// ~~~ Section 1335 ~~~
void final_cleanup() {
    small_number c; // 0 for \end, 1 for \dump
    c = cur_chr;
    if (c != 1) {
        new_line_char = -1;
    }
    if (job_name == 0) {
        open_log_file();
    }
    while (input_ptr > 0) {
        if (state == TOKEN_LIST) {
            end_token_list();
        }
        else {
            end_file_reading();
        }
    }
    while (open_parens > 0) {
        print(" )");
        decr(open_parens);
    }
    if (cur_level > LEVEL_ONE) {
        print_nl("(");
        print_esc("end occurred ");
        print("inside a group at level ");
        print_int(cur_level - LEVEL_ONE);
        print_char(')');
    }
    while (cond_ptr != null) {
        print_nl("(");
        print_esc("end occurred ");
        print("when ");
        print_cmd_chr(IF_TEST, cur_if);
        if (if_line != 0) {
            print(" on line ");
            print_int(if_line);
        }
        print(" was incomplete)");
        if_line = if_line_field(cond_ptr);
        cur_if = subtype(cond_ptr);
        temp_ptr = cond_ptr;
        cond_ptr = link(cond_ptr);
        free_node(temp_ptr, IF_NODE_SIZE);
    }
    if (history != SPOTLESS
        && (history == WARNING_ISSUED || interaction < ERROR_STOP_MODE)
        && selector == TERM_AND_LOG)
    {
        selector = TERM_ONLY;
        print_nl("(see the transcript file for additional information)");
        selector = TERM_AND_LOG;
    }
    if (c == 1) {
#ifdef INIT
        for(c = TOP_MARK_CODE; c <= SPLIT_BOT_MARK_CODE; c++) {
            if (cur_mark[c] != null) {
                delete_token_ref(cur_mark[c]);
            }
        }
        if (last_glue != MAX_HALFWORD) {
            delete_glue_ref(last_glue);
        }
        store_fmt_file();
        return;
#endif
        print_nl("(\\dump is performed only by INITEX)");
        return;
    }
}
// ~~~ End section 1335 ~~~

// ~~~ Section 1336 ~~~
#ifdef INIT
// initialize all the primitives
void init_prim() {
    no_new_control_sequence = false;

    // ~~~ Put each of TeX's primitives into the hash table, 226 ~~~
    primitive("lineskip", ASSIGN_GLUE, GLUE_BASE + LINE_SKIP_CODE);
    primitive("baselineskip", ASSIGN_GLUE, GLUE_BASE + BASELINE_SKIP_CODE);
    primitive("parskip", ASSIGN_GLUE, GLUE_BASE + PAR_SKIP_CODE);
    primitive("abovedisplayskip", ASSIGN_GLUE, GLUE_BASE + ABOVE_DISPLAY_SKIP_CODE);
    primitive("belowdisplayskip", ASSIGN_GLUE, GLUE_BASE + BELOW_DISPLAY_SKIP_CODE);
    primitive("abovedisplayshortskip",  ASSIGN_GLUE, GLUE_BASE + ABOVE_DISPLAY_SHORT_SKIP_CODE);
    primitive("belowdisplayshortskip",  ASSIGN_GLUE, GLUE_BASE + BELOW_DISPLAY_SHORT_SKIP_CODE);
    primitive("leftskip", ASSIGN_GLUE, GLUE_BASE + LEFT_SKIP_CODE);
    primitive("rightskip", ASSIGN_GLUE, GLUE_BASE + RIGHT_SKIP_CODE);
    primitive("topskip", ASSIGN_GLUE, GLUE_BASE + TOP_SKIP_CODE);
    primitive("splittopskip", ASSIGN_GLUE, GLUE_BASE + SPLIT_TOP_SKIP_CODE);
    primitive("tabskip", ASSIGN_GLUE, GLUE_BASE + TAB_SKIP_CODE);
    primitive("spaceskip", ASSIGN_GLUE, GLUE_BASE + SPACE_SKIP_CODE);
    primitive("xspaceskip", ASSIGN_GLUE, GLUE_BASE + XSPACE_SKIP_CODE);
    primitive("parfillskip", ASSIGN_GLUE, GLUE_BASE + PAR_FILL_SKIP_CODE);
    primitive("thinmuskip", ASSIGN_MU_GLUE, GLUE_BASE + THIN_MU_SKIP_CODE);
    primitive("medmuskip", ASSIGN_MU_GLUE, GLUE_BASE + MED_MU_SKIP_CODE);
    primitive("thickmuskip", ASSIGN_MU_GLUE, GLUE_BASE + THICK_MU_SKIP_CODE);
    
    // ~~~ Section 230 ~~~
    primitive("output", ASSIGN_TOKS, OUTPUT_ROUTINE_LOC);
    primitive("everypar", ASSIGN_TOKS, EVERY_PAR_LOC);
    primitive("everymath", ASSIGN_TOKS, EVERY_MATH_LOC);
    primitive("everydisplay", ASSIGN_TOKS, EVERY_DISPLAY_LOC);
    primitive("everyhbox", ASSIGN_TOKS, EVERY_HBOX_LOC);
    primitive("everyvbox", ASSIGN_TOKS, EVERY_VBOX_LOC);
    primitive("everyjob", ASSIGN_TOKS, EVERY_JOB_LOC);
    primitive("everycr", ASSIGN_TOKS, EVERY_CR_LOC);
    primitive("errhelp", ASSIGN_TOKS, ERR_HELP_LOC);
    // ~~~ End section 230 ~~~
    
    // ~~~ Section 238 ~~~
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
    // ~~~ End section 238 ~~~
    
    // ~~~ Section 248 ~~~
    primitive("parindent", ASSIGN_DIMEN, DIMEN_BASE + PAR_INDENT_CODE);
    primitive("mathsurround", ASSIGN_DIMEN, DIMEN_BASE + MATH_SURROUND_CODE);
    primitive("lineskiplimit", ASSIGN_DIMEN, DIMEN_BASE + LINE_SKIP_LIMIT_CODE);
    primitive("hsize", ASSIGN_DIMEN, DIMEN_BASE + HSIZE_CODE);
    primitive("vsize", ASSIGN_DIMEN, DIMEN_BASE + VSIZE_CODE);
    primitive("maxdepth", ASSIGN_DIMEN, DIMEN_BASE + MAX_DEPTH_CODE);
    primitive("splitmaxdepth", ASSIGN_DIMEN, DIMEN_BASE + SPLIT_MAX_DEPTH_CODE);
    primitive("boxmaxdepth", ASSIGN_DIMEN, DIMEN_BASE + BOX_MAX_DEPTH_CODE);
    primitive("hfuzz", ASSIGN_DIMEN, DIMEN_BASE + HFUZZ_CODE);
    primitive("vfuzz", ASSIGN_DIMEN, DIMEN_BASE + VFUZZ_CODE);
    primitive("delimitershortfall", ASSIGN_DIMEN, DIMEN_BASE + DELIMITER_SHORTFALL_CODE);
    primitive("nulldelimiterspace", ASSIGN_DIMEN, DIMEN_BASE + NULL_DELIMITER_SPACE_CODE);
    primitive("scriptspace", ASSIGN_DIMEN, DIMEN_BASE + SCRIPT_SPACE_CODE);
    primitive("predisplaysize", ASSIGN_DIMEN, DIMEN_BASE + PRE_DISPLAY_SIZE_CODE);
    primitive("displaywidth", ASSIGN_DIMEN, DIMEN_BASE + DISPLAY_WIDTH_CODE);
    primitive("displayindent", ASSIGN_DIMEN, DIMEN_BASE + DISPLAY_INDENT_CODE);
    primitive("overfullrule", ASSIGN_DIMEN, DIMEN_BASE + OVERFULL_RULE_CODE);
    primitive("hangindent", ASSIGN_DIMEN, DIMEN_BASE + HANG_INDENT_CODE);
    primitive("hoffset", ASSIGN_DIMEN, DIMEN_BASE + H_OFFSET_CODE);
    primitive("voffset", ASSIGN_DIMEN, DIMEN_BASE + V_OFFSET_CODE);
    primitive("emergencystretch", ASSIGN_DIMEN, DIMEN_BASE + EMERGENCY_STRETCH_CODE);
    // ~~~ End section 248 ~~~
    
    // ~~~ Section 265 ~~~
    primitive(" ", EX_SPACE, 0);
    primitive("/", ITAL_CORR, 0);
    primitive("accent", ACCENT, 0);
    primitive("advance", ADVANCE, 0);
    primitive("afterassignment", AFTER_ASSIGNMENT, 0);
    primitive("aftergroup", AFTER_GROUP, 0);
    primitive("begingroup", BEGIN_GROUP, 0);
    primitive("char", CHAR_NUM, 0);
    primitive("csname", CS_NAME, 0);
    primitive("delimiter", DELIM_NUM, 0);
    primitive("divide", DIVIDE, 0);
    primitive("endcsname", END_CS_NAME, 0);
    primitive("endgroup", END_GROUP, 0);
    text(FROZEN_END_GROUP) = str_ptr - 1; // "endgroup"
    eqtb[FROZEN_END_GROUP] = eqtb[cur_val];
    
    primitive("expandafter", EXPAND_AFTER, 0);
    primitive("font", DEF_FONT, 0);
    primitive("fontdimen", ASSIGN_FONT_DIMEN, 0);
    primitive("halign", HALIGN, 0);
    primitive("hrule", HRULE, 0);
    primitive("ignorespaces", IGNORE_SPACES, 0);
    primitive("insert", INSERT, 0);
    primitive("mark", MARK, 0);
    primitive("mathaccent", MATH_ACCENT, 0);
    primitive("mathchar", MATH_CHAR_NUM, 0);
    primitive("mathchoice", MATH_CHOICE, 0);
    primitive("multiply", MULTIPLY, 0);
    primitive("noalign", NO_ALIGN, 0);
    primitive("noboundary", NO_BOUNDARY, 0);
    primitive("noexpand", NO_EXPAND, 0);
    primitive("nonscript", NON_SCRIPT, 0);
    primitive("omit", OMIT, 0);
    primitive("parshape", SET_SHAPE, 0);
    primitive("penalty", BREAK_PENALTY, 0);
    primitive("prevgraf", SET_PREV_GRAF, 0);
    primitive("radical", RADICAL, 0);
    primitive("read", READ_TO_CS, 0);
    primitive("relax", RELAX, 256); // cf. |scan_file_name|
    text(FROZEN_RELAX) = str_ptr - 1; // "relax"
    eqtb[FROZEN_RELAX] = eqtb[cur_val];
    
    primitive("setbox", SET_BOX, 0);
    primitive("the", THE, 0);
    primitive("toks", TOKS_REGISTER, 0);
    primitive("vadjust", VADJUST, 0);
    primitive("valign", VALIGN, 0);
    primitive("vcenter", VCENTER, 0);
    primitive("vrule", VRULE, 0);
    // ~~~ End section 265 ~~~
    
    // ~~~ Section 334 ~~~
    primitive("par", PAR_END, 256); // cf. |scan_file_name|
    par_loc = cur_val;
    par_token = CS_TOKEN_FLAG + par_loc;
    // ~~~ End section 334 ~~~
    
    // ~~~ Section 376 ~~~
    primitive("input", INPUT, 0);
    primitive("endinput", INPUT, 1);
    // ~~~ End section 376 ~~~
    
    // ~~~ Section 384 ~~~
    primitive("topmark", TOP_BOT_MARK, TOP_MARK_CODE);
    primitive("firstmark", TOP_BOT_MARK, FIRST_MARK_CODE);
    primitive("botmark", TOP_BOT_MARK, BOT_MARK_CODE);
    primitive("splitfirstmark", TOP_BOT_MARK, SPLIT_FIRST_MARK_CODE);
    primitive("splitbotmark", TOP_BOT_MARK, SPLIT_BOT_MARK_CODE);
    // ~~~ End section 384 ~~~
    
    // ~~~ Section 411 ~~~
    primitive("count", REGISTER, INT_VAL);
    primitive("dimen", REGISTER, DIMEN_VAL);
    primitive("skip", REGISTER, GLUE_VAL);
    primitive("muskip", REGISTER, MU_VAL);
    // ~~~ End section 411 ~~~
    
    // ~~~ Section 416 ~~~
    primitive("spacefactor", SET_AUX, HMODE);
    primitive("prevdepth", SET_AUX, VMODE);
    primitive("deadcycles", SET_PAGE_INT, 0);
    primitive("insertpenalties", SET_PAGE_INT, 1);
    primitive("wd", SET_BOX_DIMEN, WIDTH_OFFSET);
    primitive("ht", SET_BOX_DIMEN, HEIGHT_OFFSET);
    primitive("dp", SET_BOX_DIMEN, DEPTH_OFFSET);
    primitive("lastpenalty", LAST_ITEM, INT_VAL);
    primitive("lastkern", LAST_ITEM, DIMEN_VAL);
    primitive("lastskip", LAST_ITEM, GLUE_VAL);
    primitive("inputlineno", LAST_ITEM, INPUT_LINE_NO_CODE);
    primitive("badness", LAST_ITEM, BADNESS_CODE);
    // ~~~ End section 416 ~~~
    
    // ~~~ Section 468 ~~~
    primitive("number", CONVERT, NUMBER_CODE);
    primitive("romannumeral", CONVERT, ROMAN_NUMERAL_CODE);
    primitive("string", CONVERT, STRING_CODE);
    primitive("meaning", CONVERT, MEANING_CODE);
    primitive("fontname", CONVERT, FONT_NAME_CODE);
    primitive("jobname", CONVERT, JOB_NAME_CODE);
    // ~~~ End section 468 ~~~
    
    // ~~~ Section 487 ~~~
    primitive("if", IF_TEST, IF_CHAR_CODE);
    primitive("ifcat", IF_TEST, IF_CAT_CODE);
    primitive("ifnum", IF_TEST, IF_INT_CODE);
    primitive("ifdim", IF_TEST, IF_DIM_CODE);
    primitive("ifodd", IF_TEST, IF_ODD_CODE);
    primitive("ifvmode", IF_TEST, IF_VMODE_CODE);
    primitive("ifhmode", IF_TEST, IF_HMODE_CODE);
    primitive("ifmmode", IF_TEST, IF_MMODE_CODE);
    primitive("ifinner", IF_TEST, IF_INNER_CODE);
    primitive("ifvoid", IF_TEST, IF_VOID_CODE);
    primitive("ifhbox", IF_TEST, IF_HBOX_CODE);
    primitive("ifvbox", IF_TEST, IF_VBOX_CODE);
    primitive("ifx", IF_TEST, IFX_CODE);
    primitive("ifeof", IF_TEST, IF_EOF_CODE);
    primitive("iftrue", IF_TEST, IF_TRUE_CODE);
    primitive("iffalse", IF_TEST, IF_FALSE_CODE);
    primitive("ifcase", IF_TEST, IF_CASE_CODE);
    // ~~~ End section 487 ~~~
    
    // ~~~ Section 491 ~~~
    primitive("fi", FI_OR_ELSE, FI_CODE);
    text(FROZEN_FI) = str_ptr - 1; // "fi"
    eqtb[FROZEN_FI] = eqtb[cur_val];
    primitive("or", FI_OR_ELSE, OR_CODE);
    primitive("else", FI_OR_ELSE, ELSE_CODE);
    // ~~~ End section 491 ~~~
    
    // ~~~ Section 553 ~~~
    primitive("nullfont", SET_FONT, NULL_FONT);
    text(FROZEN_NULL_FONT) = str_ptr - 1;
    eqtb[FROZEN_NULL_FONT] = eqtb[cur_val];
    // ~~~ End section 553 ~~~
    
    // ~~~ Section 780 ~~~
    primitive("span", TAB_MARK, SPAN_CODE);
    primitive("cr", CAR_RET, CR_CODE);
    text(FROZEN_CR) = str_ptr - 1; // "cr"
    eqtb[FROZEN_CR] = eqtb[cur_val];
    primitive("crcr", CAR_RET, CR_CR_CODE);
    text(FROZEN_END_TEMPLATE) = ENDTEMPLATE_STRING;
    text(FROZEN_ENDV) = ENDTEMPLATE_STRING;
    eq_type(FROZEN_ENDV) = ENDV;
    equiv(FROZEN_ENDV) = NULL_LIST;
    eq_level(FROZEN_ENDV) = LEVEL_ONE;
    eqtb[FROZEN_END_TEMPLATE] = eqtb[FROZEN_ENDV];
    eq_type(FROZEN_END_TEMPLATE) = END_TEMPLATE;
    // ~~~ End section 780 ~~~
    
    // ~~~ Section 983 ~~~
    primitive("pagegoal", SET_PAGE_DIMEN, 0);
    primitive("pagetotal", SET_PAGE_DIMEN, 1);
    primitive("pagestretch", SET_PAGE_DIMEN, 2);
    primitive("pagefilstretch", SET_PAGE_DIMEN, 3);
    primitive("pagefillstretch", SET_PAGE_DIMEN, 4);
    primitive("pagefilllstretch", SET_PAGE_DIMEN, 5);
    primitive("pageshrink", SET_PAGE_DIMEN, 6);
    primitive("pagedepth", SET_PAGE_DIMEN, 7);
    // ~~~ End section 983 ~~~
    
    // ~~~ Section 1052 ~~~
    primitive("end", STOP, 0);
    primitive("dump", STOP, 1);
    // ~~~ End section 1052 ~~~
    
    // ~~~ Section 1058 ~~~
    primitive("hskip", HSKIP, SKIP_CODE);
    primitive("hfil", HSKIP, FIL_CODE);
    primitive("hfill", HSKIP, FILL_CODE);
    primitive("hss", HSKIP, SS_CODE);
    primitive("hfilneg", HSKIP, FIL_NEG_CODE);
    primitive("vskip", VSKIP, SKIP_CODE);
    primitive("vfil", VSKIP, FIL_CODE);
    primitive("vfill", VSKIP, FILL_CODE);
    primitive("vss", VSKIP, SS_CODE);
    primitive("vfilneg", VSKIP, FIL_NEG_CODE);
    primitive("mskip", MSKIP, MSKIP_CODE);
    primitive("kern", KERN, EXPLICIT);
    primitive("mkern", MKERN, MU_GLUE);
    // ~~~ End section 1058 ~~~
    
    // ~~~ Section 1071 ~~~
    primitive("moveleft", HMOVE, 1);
    primitive("moveright", HMOVE, 0);
    primitive("raise", VMOVE, 1);
    primitive("lower", VMOVE, 0);
    
    primitive("box", MAKE_BOX, BOX_CODE);
    primitive("copy", MAKE_BOX, COPY_CODE);
    primitive("lastbox", MAKE_BOX, LAST_BOX_CODE);
    primitive("vsplit", MAKE_BOX, VSPLIT_CODE);
    primitive("vtop", MAKE_BOX, VTOP_CODE);
    primitive("vbox", MAKE_BOX, VTOP_CODE + VMODE);
    primitive("hbox", MAKE_BOX, VTOP_CODE + HMODE);
    primitive("shipout", LEADER_SHIP, A_LEADERS - 1); // |SHIP_OUT_FLAG = LEADER_FLAG - 1|
    primitive("leaders", LEADER_SHIP, A_LEADERS);
    primitive("cleaders", LEADER_SHIP, C_LEADERS);
    primitive("xleaders", LEADER_SHIP, X_LEADERS);
    // ~~~ End section 1071 ~~~
    
    // ~~~ Section 1088 ~~~
    primitive("indent", START_PAR, 1);
    primitive("noindent", START_PAR, 0);
    // ~~~ End section 1088 ~~~
    
    // ~~~ Section 1107 ~~~
    primitive("unpenalty", REMOVE_ITEM, PENALTY_NODE);
    primitive("unkern", REMOVE_ITEM, KERN_NODE);
    primitive("unskip", REMOVE_ITEM, GLUE_NODE);
    primitive("unhbox", UN_HBOX, BOX_CODE);
    primitive("unhcopy", UN_HBOX, COPY_CODE);
    primitive("unvbox", UN_VBOX, BOX_CODE);
    primitive("unvcopy", UN_VBOX, COPY_CODE);
    // ~~~ End section 1107 ~~~
    
    // ~~~ Section 1114 ~~~
    primitive("-", DISCRETIONARY, 1);
    primitive("discretionary", DISCRETIONARY, 0);
    // ~~~ End section 1114 ~~~
    
    // ~~~ Section 1141 ~~~
    primitive("eqno", EQ_NO, 0);
    primitive("leqno", EQ_NO, 1);
    // ~~~ End section 1141 ~~~
    
    // ~~~ Section 1156 ~~~
    primitive("mathord", MATH_COMP, ORD_NOAD);
    primitive("mathop", MATH_COMP, OP_NOAD);
    primitive("mathbin", MATH_COMP, BIN_NOAD);
    primitive("mathrel", MATH_COMP, REL_NOAD);
    primitive("mathopen", MATH_COMP, OPEN_NOAD);
    primitive("mathclose", MATH_COMP, CLOSE_NOAD);
    primitive("mathpunct", MATH_COMP, PUNCT_NOAD);
    primitive("mathinner", MATH_COMP, INNER_NOAD);
    primitive("underline", MATH_COMP, UNDER_NOAD);
    primitive("overline", MATH_COMP, OVER_NOAD);
    primitive("displaylimits", LIMIT_SWITCH, NORMAL);
    primitive("limits", LIMIT_SWITCH, LIMITS);
    primitive("nolimits", LIMIT_SWITCH, NO_LIMITS);
    // ~~~ End section 1156 ~~~
    
    // ~~~ Section 1169 ~~~
    primitive("displaystyle", MATH_STYLE, DISPLAY_STYLE);
    primitive("textstyle", MATH_STYLE, TEXT_STYLE);
    primitive("scriptstyle", MATH_STYLE, SCRIPT_STYLE);
    primitive("scriptscriptstyle", MATH_STYLE, SCRIPT_SCRIPT_STYLE);
    // ~~~ End section 1169 ~~~
    
    // ~~~ Section 1178 ~~~
    primitive("above", ABOVE, ABOVE_CODE);
    primitive("over", ABOVE, OVER_CODE);
    primitive("atop", ABOVE, ATOP_CODE);
    primitive("abovewithdelims", ABOVE, DELIMITED_CODE + ABOVE_CODE);
    primitive("overwithdelims", ABOVE, DELIMITED_CODE + OVER_CODE);
    primitive("atopwithdelims", ABOVE, DELIMITED_CODE + ATOP_CODE);
    // ~~~ End section 1178 ~~~
    
    // ~~~ Section 1188 ~~~
    primitive("left", LEFT_RIGHT, LEFT_NOAD);
    primitive("right", LEFT_RIGHT, RIGHT_NOAD);
    text(FROZEN_RIGHT) = str_ptr - 1; // "right"
    eqtb[FROZEN_RIGHT] = eqtb[cur_val];
    // ~~~ End section 1188 ~~~
    
    // ~~~ Section 1208 ~~~
    primitive("long", PREFIX, 1);
    primitive("outer", PREFIX, 2);
    primitive("global", PREFIX, 4);
    primitive("def", DEF, 0);
    primitive("gdef", DEF, 1);
    primitive("edef", DEF, 2);
    primitive("xdef", DEF, 3);
    // ~~~ End section 1208 ~~~
    
    // ~~~ Section 1219 ~~~
    primitive("let", LET, NORMAL);
    primitive("futurelet", LET, NORMAL + 1);
    // ~~~ End section 1219 ~~~
    
    // ~~~ Section 1222 ~~~
    primitive("chardef", SHORTHAND_DEF, CHAR_DEF_CODE);
    primitive("mathchardef", SHORTHAND_DEF, MATH_CHAR_DEF_CODE);
    primitive("countdef", SHORTHAND_DEF, COUNT_DEF_CODE);
    primitive("dimendef", SHORTHAND_DEF, DIMEN_DEF_CODE);
    primitive("skipdef", SHORTHAND_DEF, SKIP_DEF_CODE);
    primitive("muskipdef", SHORTHAND_DEF, MU_SKIP_DEF_CODE);
    primitive("toksdef", SHORTHAND_DEF, TOKS_DEF_CODE);
    // ~~~ End section 1222 ~~~
    
    // ~~~ Section 1230 ~~~
    primitive("catcode", DEF_CODE, CAT_CODE_BASE);
    primitive("mathcode", DEF_CODE, MATH_CODE_BASE);
    primitive("lccode", DEF_CODE, LC_CODE_BASE);
    primitive("uccode", DEF_CODE, UC_CODE_BASE);
    primitive("sfcode", DEF_CODE, SF_CODE_BASE);
    primitive("delcode", DEF_CODE, DEL_CODE_BASE);
    primitive("textfont", DEF_FAMILY, MATH_FONT_BASE);
    primitive("scriptfont", DEF_FAMILY, MATH_FONT_BASE + SCRIPT_SIZE);
    primitive("scriptscriptfont", DEF_FAMILY, MATH_FONT_BASE + SCRIPT_SCRIPT_SIZE);
    // ~~~ End section 1230 ~~~
    
    // ~~~ Section 1250 ~~~
    primitive("hyphenation", HYPH_DATA, 0);
    primitive("patterns", HYPH_DATA, 1);
    // ~~~ End section 1250 ~~~
    
    // ~~~ Section 1254 ~~~
    primitive("hyphenchar", ASSIGN_FONT_INT, 0);
    primitive("skewchar", ASSIGN_FONT_INT, 1);
    // ~~~ End section 1254 ~~~
    
    // ~~~ Section 1262 ~~~
    primitive("batchmode", SET_INTERACTION, BATCH_MODE);
    primitive("nonstopmode", SET_INTERACTION, NONSTOP_MODE);
    primitive("scrollmode", SET_INTERACTION, SCROLL_MODE);
    primitive("errorstopmode", SET_INTERACTION, ERROR_STOP_MODE);
    // ~~~ End section 1262 ~~~
    
    // ~~~ Section 1272 ~~~
    primitive("openin", IN_STREAM, 1);
    primitive("closein", IN_STREAM, 0);
    // ~~~ End section 1272 ~~~
    
    // ~~~ Section 1277 ~~~
    primitive("message", MESSAGE, 0);
    primitive("errmessage", MESSAGE, 1);
    // ~~~ End section 1277 ~~~
    
    // ~~~ Section 1286 ~~~
    primitive("lowercase", CASE_SHIFT, LC_CODE_BASE);
    primitive("uppercase", CASE_SHIFT, UC_CODE_BASE);
    // ~~~ End section 1286 ~~~
    
    // ~~~ Section 1291 ~~~
    primitive("show", XRAY, SHOW_CODE);
    primitive("showbox", XRAY, SHOW_BOX_CODE);
    primitive("showthe", XRAY, SHOW_THE_CODE);
    primitive("showlists", XRAY, SHOW_LISTS_CODE);
    // ~~~ End section 1291 ~~~
    
    // ~~~ Section 1344 ~~~
    primitive("openout", EXTENSION, OPEN_NODE);
    primitive("write", EXTENSION, WRITE_NODE);
    write_loc = cur_val;
    primitive("closeout", EXTENSION, CLOSE_NODE);
    primitive("special", EXTENSION, SPECIAL_NODE);
    primitive("immediate", EXTENSION, IMMEDIATE_CODE);
    primitive("setlanguage", EXTENSION, SET_LANGUAGE_CODE);
    // ~~~ End section 1344 ~~~
    // ~~~ End section 226 ~~~
    
    no_new_control_sequence = true;
}
#endif
// ~~~ End section 1336 ~~~

// ~~~ Section 1338 ~~~
#ifdef DEBUG
 // routine to display various things
void debug_help() {
    int k, l, m, n;
    int err; // handling input error
    clear_terminal;
    while(true) {
        print_nl("debug # (-1 to exit):");
        update_terminal;
        err = scanf("%d", &m);
        if (err != 1) {
            print("?");
            continue;
        }
        if (m < 0) {
            return;
        }
        err = scanf("%d", &n);
        if (err != 1) {
            print("?");
            continue;
        }
        switch (m) {
        // ~~~ Numbered cases for |debug_help|, 1339 ~~~
        case 1:
            print_word(mem[n]);
            break; // display |mem[n]| in all forms
        
        case 2:
            print_int(info(n));
            break;
        
        case 3:
            print_int(link(n));
            break;
        
        case 4:
            print_word(eqtb[n]);
            break;
        
        case 5:
            print_word(font_info[n]);
            break;
        
        case 6:
            print_word(save_stack[n]);
            break;
        
        case 7:
            // show a box, abbreviated by |show_box_depth| and |show_box_breadth|
            show_box(n);
            break;
           
        case 8:
            // show a box in its entirety
            breadth_max = 10000;
            depth_threshold = POOL_SIZE - pool_ptr - 10;
            show_node_list(n); 
            break;
        
        case 9:
            show_token_list(n, null, 1000);
            break;
        
        case 10:
            slow_print(n);
            break;
        
        case 11:
            // check wellformedness; print new busy locations if |n > 0|
            check_mem(n > 0);
            break;
        
        case 12:
            // look for pointers to |n|
            search_mem(n);
            break;
        
        case 13:
            err = scanf("%d", &l);
            if (err != 1) {
                print("?");
                continue;
            }
            print_cmd_chr(n, l);
            break;
        
        case 14:
            for(k = 0; k <= n; k++) {
                print_strnumber(buffer[k]);
            }
            break;
        
        case 15:
            font_in_short_display = NULL_FONT;
            short_display(n);
            break;
        
        case 16:
            panicking = !panicking;
            break;
        // ~~~ End section 1339 ~~~
        
        default:
            print("?");
        }
    }
}
#endif
// ~~~ End section 1338 ~~~
// ~~~ End section 1333 ~~~
// ~~~ End section 1330 ~~~
