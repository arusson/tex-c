// ~~~ Section 20 ~~~
// ~~~ Start file |strings.c|, 1382 ~~~
#include <string.h>
#include "strings.h"
#include "texerror.h"
// ~~~ End section 1382 ~~~

// specifies conversion of input characters
const ASCII_code XORD[256] = {
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
};

// specifies conversion of output characters
const unsigned char XCHR[256] = {
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', '!', '"', '#', '$', '%', '&', '\'',
    '(', ')', '*', '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', ':', ';', '<', '=', '>', '?',
    '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
    'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
    'x', 'y', 'z', '{', '|', '}', '~', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
};
// ~~~ End section 20 ~~~

// ~~~ Section 43 ~~~
// current string enters the pool
str_number make_string() {
    if (str_ptr == MAX_STRINGS) {
        overflow("number of strings", MAX_STRINGS - init_str_ptr);
    }
    incr(str_ptr);
    str_start[str_ptr] = pool_ptr;
    return str_ptr - 1;
}
// ~~~ End section 43 ~~~

// ~~~ Section 45 ~~~
// test equality of strings
int str_eq_buf(str_number s, int k) {
    pool_pointer j;     // running index
    bool result = true; // result of comparison;
    j = str_start[s];
    while (j < str_start[s + 1]) {
        if (str_pool[j] != buffer[k]) {
            result = false;
            break; // Goto not_found
        }
        incr(j);
        incr(k);
    }
    // not_found:
    return result;
}
// ~~~ End section 45 ~~~

// ~~~ Section 46 ~~~
// test equality of strings
int str_eq_str(str_number s, str_number t) {
    pool_pointer j, k;   // running indices
    bool result = false; // result of comparison
    if (length(s) != length(t)) {
        goto not_found;
    }
    j = str_start[s];
    k = str_start[t];
    while (j < str_start[s + 1]) {
        if (str_pool[j] != str_pool[k]) {
            goto not_found;
        }
        incr(j);
        incr(k);
    }
    result = true;
not_found:
    return result;
}
// ~~~ End section 46 ~~~

// ~~~ Section 47 ~~~
#ifdef INIT
// initializes the string pool
void get_strings_started() {
    int k, l; // small indices or counters
    pool_ptr = 0;
    str_ptr = 0;
    str_start[0] = 0;
    // ~~~ Make the first 256 strings, 48 ~~~
    for (k = 0; k < 256; k++) {
        if (k < ' ' || k > '~') {
            append_char('^');
            append_char('^');
            if (k < 64) {
                append_char(k + 64);
            }
            else if (k < 128) {
                append_char(k - 64);
            }
            else {
                app_lc_hex(k / 16);
                app_lc_hex(k % 16);
            }
        }
        else {
            append_char(k);
        }
        make_string();
    }
    // ~~~ End section 48 ~~~
    // ~~~ Read the other strings, 51 ~~~
    put_string(""); // Empty string, its number should be 256
    
    // ~~~ Section 258 ~~~
    put_string("notexpanded:"); // NOTEXPANDED_STRING: 257
    // ~~~ End section 258 ~~~
    
    // ~~~ Section 514 ~~~
    put_string("TeXinputs/"); // TEX_AREA: 258
    put_string("TeXfonts/");  // TEX_FONT_AREA: 259
    // ~~~ End section 514 ~~~
    
    // ~~~ Section 520 ~~~
    put_string(".fmt"); // FMT_EXT: 260
    // ~~~ End section 520 ~~~
    
    // ~~~ Section 530 ~~~
    put_string(".tex"); // TEX_EXT: 261
    // ~~~ End section 530 ~~~
    
    // ~~~ Section 532 ~~~
    put_string(".dvi"); // DVI_EXT: 262
    // ~~~ End section 532 ~~~
    
    // ~~~ Section 534 ~~~
    put_string("texput"); // TEXPUT_STRING: 263
    put_string(".log");   // LOG_EXT: 264
    // ~~~ End section 534 ~~~
    
    // ~~~ Section 552 ~~~
    put_string("nullfont"); // NULLFONT_STRING: 265
    // ~~~ End section 552 ~~~
    
    // ~~~ Section 563 ~~~
    put_string(".tfm"); // TFM_EXT: 266
    // ~~~ End section 563 ~~~
    
    // ~~~ Section 780 ~~~
    put_string("endtemplate"); // ENDTEMPLATE_STRING: 267
    // ~~~ End section 780 ~~~
    
    // ~~~ Section 1216 ~~~
    put_string("inaccessible"); // INACCESSIBLE_STRING: 268
    // ~~~ End section 1216 ~~~
    
    // ~~~ Section 1257 ~~~
    put_string("FONT"); // FONT_STRING: 269
    // ~~~ End section 1257 ~~~
    
    // ~~~ Section 1301 ~~~
    put_string(" (INITEX)"); // INITEX_IDENT_STRING: 270
    // ~~~ End section 1301 ~~~
    
    // ~~~ Section 1369 ~~~
    put_string("endwrite"); // ENDWRITE_STRING: 271
    // ~~~ End section 1369 ~~~
    // ~~~ End section 51 ~~~
}
#endif
// ~~~ End section 47 ~~~

// ~~~ Section 51 ~~~
str_number put_string(char *s) {
    int n = strlen(s);
    str_room(n);
    memcpy(&str_pool[pool_ptr], s, n);
    pool_ptr += n;
    return make_string();
}
// ~~~ End section 51 ~~~
