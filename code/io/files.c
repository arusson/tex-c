// ~~~ Section 27 ~~~
// ~~~ Start file |files.c|, 1382 ~~~
#include <stdlib.h>
#include "datastructures.h"
#include "texerror.h"
#include "parser.h"
// ~~~ End section 1382 ~~~

// open a text file for input
int a_open_in(alpha_file *f) {
    *f = fopen(name_of_file, "r");
    return *f != NULL;
}

// open a text file for output
int a_open_out(alpha_file *f) {
    *f = fopen(name_of_file, "w");
    return *f != NULL;
}

// open a binary file for input
int b_open_in(byte_file *f) {
    *f = fopen(name_of_file, "rb");
    return *f != NULL;
}

// open a binary file for output
int b_open_out(byte_file *f) {
    *f = fopen(name_of_file, "wb");
    return *f != NULL;
}

// open a word file for input
int w_open_in(word_file *f) {
    *f = fopen(name_of_file, "rb");
    return *f != NULL;
}

// open a word file for output
int w_open_out(word_file *f) {
    *f = fopen(name_of_file, "wb");
    return *f != NULL;
}
// ~~~ End section 27 ~~~

// ~~~ Section 28 ~~~
// close a text file
void a_close(alpha_file f) {
    fclose(f);
}

// close a binary file
void b_close(byte_file f) {
    fclose(f);
}

// close a word file
void w_close(word_file f) {
    fclose(f);
}
// ~~~ End section 28 ~~~

// ~~~ Section 31 ~~~
// inputs the next line or returns |false|
int input_ln(alpha_file f) {
    int last_nonblank; // |last| with trailing blanks removed
    int c;

    last = first;
    last_nonblank = first;
    while ((c = fgetc(f)) != '\n' && c != EOF) {
        if (last >= max_buf_stack) {
            max_buf_stack = last + 1;
            if (max_buf_stack == BUF_SIZE) {
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
        buffer[last] = XORD[c];
        incr(last);
        if (buffer[last - 1] != ' ') {
            last_nonblank = last;
        }
    }
    if (c == EOF && last == first) {
        return false;
    }
    last = last_nonblank;
    return true;
}
// ~~~ End section 31 ~~~

// ~~~ Section 534 ~~~
void open_log_file() {
    int old_setting; // previous |selector| setting
    int k;           // index into |months| and |buffer|
    int l;           // end of first input line
    char *months[12] = {
        "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
        "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
    }; // abbreviations of month names
    old_setting = selector;
    if (job_name == 0) {
        job_name = TEXPUT_STRING; // "texput"
    }
    pack_job_name(LOG_EXT);
    while (!a_open_out(&log_file)) {
        // ~~~ Try to get a different log file name, 535 ~~~
        selector = TERM_ONLY;
        prompt_file_name("transcript file name", LOG_EXT);
        // ~~~ End section 535 ~~~
    }
    log_name = make_name_string();
    selector = LOG_ONLY;
    log_opened = true;
    // ~~~ Print the banner line, including the date and time, 536 ~~~
    wlog(BANNER);
    slow_print(format_ident);
    print("  ");
    print_int(sys_day);
    print_char(' ');
    wlog("%s", months[sys_month - 1]);
    print_char(' ');
    print_int(sys_year);
    print_char(' ');
    print_two(sys_time / 60);
    print_char(':');
    print_two(sys_time % 60);
    // ~~~ End section 536 ~~~
    input_stack[input_ptr] = cur_input; // make sure bottom level is in memory
    print_nl("**");
    l = input_stack[0].limit_field; // last position of first line
    if (buffer[l] == end_line_char) {
        decr(l);
    }
    for(k = 1; k <= l; k++) {
        print_strnumber(buffer[k]);
    }
    print_ln(); // now the transcript file contains the first line of input
    selector = old_setting + 2; // |LOG_ONLY| or |TERM_AND_LOG|
}
// ~~~ End section 534 ~~~
