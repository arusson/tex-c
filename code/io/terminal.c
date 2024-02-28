// ~~~ Section 71 ~~~
// ~~~ Start file |terminal.c|, 1382 ~~~
#include <string.h>
#include "texerror.h"
#include "io.h"
#include "parser.h"
// ~~~ End section 1382 ~~~

// gets a line from the terminal
void term_input() {
    int k; // index into |buffer|
    update_terminal; // now the user sees the prompt for sure
    if (!input_ln(stdin)) {
        fatal_error("End of file on the terminal");
    }
    term_offset = 0; // the user's line ended with <return>
    decr(selector); // prepare to echo the input
    if (last != first) {
        for(k = first; k < last; k++) {
            print_strnumber(buffer[k]);
        }
    }
    print_ln();
    incr(selector); // restore previous status
}
// ~~~ End section 71 ~~~

// ~~~ Section 530 ~~~
void prompt_file_name(char *s, str_number e) {
    int k; // index into |buffer|
    if (strcmp(s, "input file name") == 0) {
        print_err("I can't find file `");
    }
    else {
        print_err("I can't write on file `");
    }
    print_file_name(cur_name, cur_area, cur_ext);
    print("'.");
    if (e == TEX_EXT) {
        show_context();
    }
    print_nl("Please type another ");
    print(s);
    if (interaction < SCROLL_MODE) {
        fatal_error("*** (job aborted, file error in nonstop mode)");
    }
    clear_terminal;
    prompt_input(": ");
    // ~~~ Scan file name in the buffer, 531 ~~~
    begin_name();
    k = first;
    while (buffer[k] == ' ' && k < last) {
        incr(k);
    }
    while(true) {
        if (k == last || !more_name(buffer[k])) {
            break; // Goto done
        }
        incr(k);
    }
    // done:
    end_name();
    // ~~~ End section 531 ~~~
    if (cur_ext == EMPTY_STRING) {
        cur_ext = e;
    }
    pack_cur_name;
}
// ~~~ End section 530 ~~~
