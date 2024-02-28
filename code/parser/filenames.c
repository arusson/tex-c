// ~~~ Section 515 ~~~
// ~~~ Start file |filenames.c|, 1382 ~~~
#include "texerror.h"
#include "parser.h"
#include "strings.h"
// ~~~ End section 1382 ~~~

void begin_name() {
    area_delimiter = 0;
    ext_delimiter = 0;
}
// ~~~ End section 515 ~~~

// ~~~ Section 516 ~~~
bool more_name(ASCII_code c) {
    if (c == ' ') {
        return false;
    }
    else {
        str_room(1);
        append_char(c); // contribute |c| to the current string
        if (c == '/') {
            area_delimiter = cur_length;
            ext_delimiter = 0;
        }
        else if (c == '.' && ext_delimiter == 0) {
            ext_delimiter = cur_length;
        }
        return true;
    }
}
// ~~~ End section 516 ~~~

// ~~~ Section 517 ~~~
void end_name() {
    if (str_ptr + 3 > MAX_STRINGS) {
        overflow("number of strings", MAX_STRINGS - init_str_ptr);
    }
    if (area_delimiter == 0) {
        cur_area = EMPTY_STRING;
    }
    else {
        cur_area = str_ptr;
        str_start[str_ptr + 1] = str_start[str_ptr] + area_delimiter;
        incr(str_ptr);
    }
    if (ext_delimiter == 0) {
        cur_ext = EMPTY_STRING;
        cur_name = make_string();
    }
    else {
        cur_name = str_ptr;
        str_start[str_ptr + 1] = str_start[str_ptr] + ext_delimiter - area_delimiter - 1;
        incr(str_ptr);
        cur_ext = make_string();
    }
}
// ~~~ End section 517 ~~~

// ~~~ Section 519 ~~~
void pack_file_name(str_number n, str_number a, str_number e) {
    int k; // number of positions filled in |name_of_file|
    ASCII_code c; // character being packed
    int j; // index into |str_pool|
    k = 0;
    for(j = str_start[a]; j <= str_start[a + 1] - 1; j++) {
        append_to_name(str_pool[j]);
    }
    for(j = str_start[n]; j <= str_start[n + 1] - 1; j++) {
        append_to_name(str_pool[j]);
    }
    for(j = str_start[e]; j <= str_start[e + 1] - 1; j++) {
        append_to_name(str_pool[j]);
    }
    if (k <= FILE_NAME_SIZE) {
        name_length = k;
    }
    else {
        name_length = FILE_NAME_SIZE;
    }
    append_to_name_nul;
}
// ~~~ End section 519 ~~~

// ~~~ Section 525 ~~~
str_number make_name_string() {
    int k; // index into |name_of_file|
    if (pool_ptr + name_length > POOL_SIZE
        || str_ptr == MAX_STRINGS
        || cur_length > 0)
    {
        return '?';
    }
    else {
        for(k = 0; k < name_length; k++) {
            append_char(XORD[(int)name_of_file[k]]);
        }
        return make_string();
    }
}
// ~~~ End section 525 ~~~

// ~~~ Section 526 ~~~
void scan_file_name() {
    name_in_progress = true;
    begin_name();
    // ~~~ Get the next non-blank non-call token, 406 ~~~
    do {
        get_x_token();
    } while (cur_cmd == SPACER);
    // ~~~ End section 406 ~~~
    while(true) {
        if (cur_cmd > OTHER_CHAR || cur_chr > 255) {
              // not a character
            back_input();
            break; // Goto done
        }
        if (!more_name(cur_chr)) {
            break; // Goto done
        }
        get_x_token();
    }
    // done:
    end_name();
    name_in_progress = false;
}
// ~~~ End section 526 ~~~

// ~~~ Section 529 ~~~
void pack_job_name(str_number s) {
    // |s = ".log"|, |".dvi"|, or |FORMAT_EXTENSION|
    cur_area = EMPTY_STRING;
    cur_ext = s;
    cur_name = job_name;
    pack_cur_name;
}
// ~~~ End section 529 ~~~

// ~~~ Section 537 ~~~
// TeX will \input something
void start_input() {
    scan_file_name(); // set |cur_name| to desired file name
    if (cur_ext == EMPTY_STRING) {
        cur_ext = TEX_EXT;
    }
    pack_cur_name;
    while(true) {
        begin_file_reading(); // set up |cur_file| and new level of input
        if (a_open_in(&cur_file)) {
            break; // Goto done
        }
        if (cur_area == EMPTY_STRING) {
            pack_file_name(cur_name, TEX_AREA, cur_ext);
            if (a_open_in(&cur_file)) {
                break; // Goto done
            }
        }
        end_file_reading(); // remove the level that didn't work
        prompt_file_name("input file name", TEX_EXT);
    }
    // done:
    name = make_name_string();
    if (job_name == 0) {
        job_name = cur_name;
        open_log_file();
    } // |open_log_file| doesn't |show_context|, so |limit| and |loc| needn't be set to meaningful values yet
    if (term_offset + length(name) > MAX_PRINT_LINE - 2) {
        print_ln();
    }
    else if (term_offset > 0 || file_offset > 0) {
        print_char(' ');
    }
    print_char('(');
    incr(open_parens);
    slow_print(name);
    update_terminal;
    state = NEW_LINE;
    if (name == str_ptr - 1) {
        // conserve string pool space (but see note above)
        flush_string;
        name = cur_name;
    }
    // ~~~ Read the first line of the new file, 538 ~~~
    line = 1;
    input_ln(cur_file); // ignore returned value
    firm_up_the_line();
    if (end_line_char_inactive) {
        decr(limit);
    }
    else {
        buffer[limit] = end_line_char;
    }
    first = limit + 1;
    loc = start;
    // ~~~ End section 538 ~~~
}
// ~~~ End section 537 ~~~
