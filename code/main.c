// ~~~ Section 1332 ~~~
// ~~~ Start file |main.c|, 1382 ~~~
#include <stdlib.h>
#include <string.h>
#include "builder.h"
#include "io.h"
#include "parser.h"
// ~~~ End section 1382 ~~~

// |start_here|
int main(int argc, char *argv[]) {
    history = FATAL_ERROR_STOP; // in case we quit during initialization
    // if ready_already = 314159 then goto start_of_TEX
    // ~~~ Check the "constant" values for consistency, 14 ~~~
    bad = 0;
    if (HALF_ERROR_LINE < 30 || HALF_ERROR_LINE > ERROR_LINE - 15) {
        bad = 1;
    }
    if (MAX_PRINT_LINE < 60) {
        bad = 2;
    }
    if (DVI_BUF_SIZE % 8 != 0) {
        bad = 3;
    }
    if (MEM_BOT + 1100 > MEM_TOP) {
        bad = 4;
    }
    if (HASH_PRIME > HASH_SIZE) {
        bad = 5;
    }
    if (MAX_IN_OPEN >= 128) {
        bad = 6;
    }
    if (MEM_TOP < 256 + 11) {
        bad = 7; // we will want |NULL_LIST > 255|
    }
    
    // ~~~ Section 111 ~~~
#ifdef INIT
    if (MEM_MIN != MEM_BOT || MEM_MAX != MEM_TOP) {
        bad = 10;
    }
#endif
    if (MEM_MIN > MEM_BOT || MEM_MAX < MEM_TOP) {
        bad = 10;
    }
    if (MIN_QUARTERWORD > 0 || MAX_QUARTERWORD < 127) {
        bad = 11;
    }
    if (MIN_HALFWORD > 0 || MAX_HALFWORD < 32767) {
        bad = 12;
    }
    if (MIN_QUARTERWORD < MIN_HALFWORD || MAX_QUARTERWORD > MAX_HALFWORD) {
        bad = 13;
    }
    if (MEM_MIN < MIN_HALFWORD
        || MEM_MAX >= MAX_HALFWORD
        || MEM_BOT - MEM_MIN > MAX_HALFWORD + 1)
    {
        bad = 14;
    }
    if (FONT_BASE < MIN_QUARTERWORD || FONT_MAX > MAX_QUARTERWORD) {
        bad = 15;
    }
    if (FONT_MAX > FONT_BASE + 256) {
        bad = 16;
    }
    if (SAVE_SIZE > MAX_HALFWORD || MAX_STRINGS > MAX_HALFWORD) {
        bad = 17;
    }
    if (BUF_SIZE > MAX_HALFWORD) {
        bad = 18;
    }
    if (MAX_QUARTERWORD - MIN_QUARTERWORD < 255) {
        bad = 19;
    }
    // ~~~ End section 111 ~~~
    
    // ~~~ Section 290 ~~~
    if (CS_TOKEN_FLAG + UNDEFINED_CONTROL_SEQUENCE > MAX_HALFWORD) {
        bad = 21;
    }
    // ~~~ End section 290 ~~~
    
    // ~~~ Section 522 ~~~
    if (FORMAT_DEFAULT_LENGTH > FILE_NAME_SIZE) {
        bad = 31;
    }
    // ~~~ End section 522 ~~~
    
    // ~~~ Section 1249 ~~~
    if (2*MAX_HALFWORD < MEM_TOP - MEM_MIN) {
        bad = 41;
    }
    // ~~~ End section 1249 ~~~
    // ~~~ End section 14 ~~~
    if (bad > 0) {
        printf(
            "Ouch---my internal constants have been clobbered!" "---case %d\n", bad
        );
        exit(0);
    }
    initialize(); // set global variables to their starting values
#ifdef INIT
    get_strings_started();
    init_prim(); // call |primitive| for each primitive
    init_str_ptr = str_ptr;
    init_pool_ptr = pool_ptr;
    fix_date_and_time();
#endif
    // ready_already = 314159; Sorry, not supported
    // start_of_TEX:
    // ~~~ Initialize the output routines, 55 ~~~
    selector = TERM_ONLY;
    tally = 0;
    term_offset = 0;
    file_offset = 0;
    
    // ~~~ Section 61 ~~~
    wterm(BANNER);
    if (format_ident == 0) {
        wterm_ln(" (no format preloaded)");
    }
    else {
        slow_print(format_ident);
        print_ln();
    }
    update_terminal;
    // ~~~ End section 61 ~~~
    
    // ~~~ Section 528 ~~~
    job_name = 0;
    name_in_progress = false;
    log_opened = false;
    // ~~~ End section 528 ~~~
    
    // ~~~ Section 533 ~~~
    output_file_name = 0;
    // ~~~ End section 533 ~~~
    // ~~~ End section 55 ~~~
    // ~~~ Get the first line of input and prepare to start, 1337 ~~~
    // ~~~ Initialize the input routines, 331 ~~~
    input_ptr = 0;
    max_in_stack = 0;
    in_open = 0;
    open_parens = 0;
    max_buf_stack = 0;
    param_ptr = 0;
    max_param_stack = 0;
    memset(buffer, 0, BUF_SIZE + 1);
    scanner_status = NORMAL;
    warning_index = null;
    first = 1;
    state = NEW_LINE;
    start = 1;
    index = 0;
    line = 0;
    name = 0;
    force_eof = false;
    align_state = 1000000;
    if (!init_terminal(argc, argv)) {
        exit(0);
    }
    limit = last;
    first = last + 1; // |init_terminal| has set |loc| and |last|
    // ~~~ End section 331 ~~~
    if (format_ident == 0 || buffer[loc] == '&') {
        if (format_ident != 0) {
            initialize(); // erase preloaded format
        }
        if (!open_fmt_file()) {
            exit(0);
        }
        if (!load_fmt_file()) {
            w_close(fmt_file);
            exit(0);
        }
        w_close(fmt_file);
        while (loc < limit && buffer[loc] == ' ') {
            incr(loc);
        }
    }
    if (end_line_char_inactive) {
        decr(limit);
    }
    else {
        buffer[limit] = end_line_char;
    }
    fix_date_and_time();
    // ~~~ Initialize the print |selector| based on |interaction|, 75 ~~~
    if (interaction == BATCH_MODE) {
        selector = NO_PRINT;
    }
    else {
        selector = TERM_ONLY;
    }
    // ~~~ End section 75 ~~~
    if (loc < limit && cat_code(buffer[loc]) != ESCAPE) {
        // \input assumed
        start_input();
    }
    // ~~~ End section 1337 ~~~
    history = SPOTLESS; // ready to go!
    main_control();     // come to life
    final_cleanup();    // prepare for death
    // end_of_TEX:
    close_files_and_terminate();
    return 0;
}
// ~~~ End section 1332 ~~~
