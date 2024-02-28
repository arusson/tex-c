// ~~~ Section 1348 ~~~
// ~~~ Start file |extensions.c|, 1382 ~~~
#include "extensions.h"
#include "parser.h"
#include "dvi.h"
#include "builder.h"
#include "texerror.h"
// ~~~ End section 1382 ~~~

// ~~~ Declare procedures needed in |do_extension|, 1349 ~~~
void new_whatsit(small_number s, small_number w) {
    pointer p; // the new node
    p = get_node(w);
    type(p) = WHATSIT_NODE;
    subtype(p) = s;
    link(tail) = p;
    tail = p;
}

// ~~~ Section 1350 ~~~
void new_write_whatsit(small_number w) {
    new_whatsit(cur_chr, w);
    if (w != WRITE_NODE_SIZE) {
        scan_four_bit_int();
    }
    else {
        scan_int();
        if (cur_val < 0) {
            cur_val = 17;
        }
        else if (cur_val > 15) {
            cur_val = 16;
        }
    }
    write_stream(tail) = cur_val;
}
// ~~~ End section 1350 ~~~
// ~~~ End section 1349 ~~~

void do_extension() {
    int k; // all-purpose integer
    pointer p; // all-purpose pointer
    switch (cur_chr) {
    case OPEN_NODE:
        // ~~~ Implement \openout, 1351 ~~~
        new_write_whatsit(OPEN_NODE_SIZE);
        scan_optional_equals();
        scan_file_name();
        open_name(tail) = cur_name;
        open_area(tail) = cur_area;
        open_ext(tail) = cur_ext;
        // ~~~ End section 1351 ~~~
        break;
    
    case WRITE_NODE:
        // ~~~ Implement \write, 1352 ~~~
        k = cur_cs;
        new_write_whatsit(WRITE_NODE_SIZE);
        cur_cs = k;
        p = scan_toks(false, false);
        write_tokens(tail) = def_ref;
        // ~~~ End section 1352 ~~~
        break;
    
    case CLOSE_NODE:
        // ~~~ Implement \closeout, 1353 ~~~
        new_write_whatsit(WRITE_NODE_SIZE);
        write_tokens(tail) = null;
        // ~~~ End section 1353 ~~~
        break;
    
    case SPECIAL_NODE:
        // ~~~ Implement \special, 1354 ~~~
        new_whatsit(SPECIAL_NODE, WRITE_NODE_SIZE);
        write_stream(tail) = null;
        p = scan_toks(false, true);
        write_tokens(tail) = def_ref;
        // ~~~ End section 1354 ~~~
        break;
    
    case IMMEDIATE_CODE:
        // ~~~ Implement \immediate, 1375 ~~~
        get_x_token();
        if (cur_cmd == EXTENSION && cur_chr <= CLOSE_NODE) {
            p = tail;
            do_extension(); // append a whatsit node
            out_what(tail); // do the action immediately
            flush_node_list(tail);
            tail = p;
            link(p) = null;
        }
        else {
            back_input();
        }
        // ~~~ End section 1375 ~~~
        break;
    
    case SET_LANGUAGE_CODE:
        // ~~~ Implement \setlanguage, 1377 ~~~
        if (abs(mode) != HMODE) {
            report_illegal_case();
        }
        else {
            new_whatsit(LANGUAGE_NODE, SMALL_NODE_SIZE);
            scan_int();
            if (cur_val <= 0) {
                clang = 0;
            }
            else if (cur_val > 255) {
                clang = 0;
            }
            else {
                clang = cur_val;
            }
            what_lang(tail) = clang;
            what_lhm(tail) = norm_min(left_hyphen_min);
            what_rhm(tail) = norm_min(right_hyphen_min);
        }
        // ~~~ End section 1377 ~~~
        break;
    
    default:
        confusion("ext1");
    }
}
// ~~~ End section 1348 ~~~
