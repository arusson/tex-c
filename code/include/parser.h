// ~~~ Section 344 ~~~
// ~~~ Start file |parser.h|, 1381 ~~~
#ifndef PARSER_H_
#define PARSER_H_

#include "datastructures.h"
// ~~~ End section 1381 ~~~

#define any_state_plus(X)   \
    case MID_LINE + (X):    \
    case SKIP_BLANKS + (X): \
    case NEW_LINE + (X)
// ~~~ End section 344 ~~~

// ~~~ Section 347 ~~~
#define add_delims_to(X)   \
    case (X) + MATH_SHIFT: \
    case (X) + TAB_MARK:   \
    case (X) + MAC_PARAM:  \
    case (X) + SUB_MARK:   \
    case (X) + LETTER:     \
    case (X) + OTHER_CHAR
// ~~~ End section 347 ~~~

// ~~~ Section 352 ~~~
#define is_hex(X) (((X) >= '0' && (X) <= '9' ) || ((X) >= 'a' && (X) <= 'f'))
#define hex_to_cur_chr                            \
    do {                                          \
        if (c <= '9') {                           \
            cur_chr = c - '0';                    \
        }                                         \
        else {                                    \
            cur_chr = c - 'a' + 10;               \
        }                                         \
        if (cc <= '9') {                          \
            cur_chr = 16*cur_chr + cc - '0';      \
        }                                         \
        else {                                    \
            cur_chr = 16*cur_chr + cc - 'a' + 10; \
        }                                         \
    } while (0)
// ~~~ End section 352 ~~~

// ~~~ Section 360 ~~~
#define end_line_char_inactive (end_line_char < 0 || end_line_char > 255)
// ~~~ End section 360 ~~~

// ~~~ Section 371 ~~~
#define store_new_token(X) \
    q = get_avail();       \
    link(p) = q;           \
    info(q) = (X);         \
    p = q // |link(p)| is |null|

#define fast_store_new_token(X) \
    fast_get_avail(q);          \
    link(p) = q;                \
    info(q) = (X);              \
    p = q // |link(p)| is |null|
// ~~~ End section 371 ~~~

// ~~~ Section 382 ~~~
#define top_mark         cur_mark[TOP_MARK_CODE]
#define first_mark       cur_mark[FIRST_MARK_CODE]
#define bot_mark         cur_mark[BOT_MARK_CODE]
#define split_first_mark cur_mark[SPLIT_FIRST_MARK_CODE]
#define split_bot_mark   cur_mark[SPLIT_BOT_MARK_CODE]
// ~~~ End section 382 ~~~

// ~~~ Section 413 ~~~
#define scanned_result(X, Y) \
    cur_val = (X);           \
    cur_val_level = (Y)
// ~~~ End section 413 ~~~

// ~~~ Section 448 ~~~
#define scan_normal_dimen scan_dimen(false, false, false)
// ~~~ End section 448 ~~~

// ~~~ Section 458 ~~~
#define set_conversion(X, Y) num = (X); denom = (Y)
// ~~~ End section 458 ~~~

// ~~~ Section 506 ~~~
#define get_x_token_or_active_char                           \
    do {                                                     \
        get_x_token();                                       \
        if (cur_cmd == RELAX && cur_chr == NO_EXPAND_FLAG) { \
            cur_cmd = ACTIVE_CHAR;                           \
            cur_chr = cur_tok - CS_TOKEN_FLAG - ACTIVE_BASE; \
        }                                                    \
    } while (0)
// ~~~ End section 506 ~~~

// ~~~ Section 519 ~~~
#define append_to_name(X)              \
    do {                               \
        c = (X);                       \
        if (k < FILE_NAME_SIZE) {      \
            name_of_file[k] = XCHR[c]; \
        }                              \
        incr(k);                       \
    } while (0)

#define append_to_name_nul name_of_file[name_length] = '\0'
// ~~~ End section 519 ~~~

// ~~~ Section 529 ~~~
#define pack_cur_name pack_file_name(cur_name, cur_area, cur_ext)
// ~~~ End section 529 ~~~

// ~~~ Section 934 ~~~
#define set_cur_lang               \
    do {                           \
        if (language <= 0) {       \
            cur_lang = 0;          \
        }                          \
        else if (language > 255) { \
            cur_lang = 0;          \
        }                          \
        else {                     \
            cur_lang = language;   \
        }                          \
    } while(0)

void new_hyph_exceptions();
// ~~~ End section 934 ~~~

// ~~~ Section 947 ~~~
#define trie_root trie_l[0] // root of the linked trie
// ~~~ End section 947 ~~~

// ~~~ Section 950 ~~~
#define trie_ref     trie_hash      // where linked trie families go into |trie|
#define trie_back(X) hh_lh(trie[X]) // backward links in |trie| holes
// ~~~ End section 950 ~~~

// ~~~ Section 1381 ~~~
// sets |cur_cmd|, |cur_chr|, |cur_cs| to next token
void get_next();

void firm_up_the_line();

// sets |cur_cmd|, |cur_chr|, |cur_tok|
void get_token();

void expand();

void insert_relax();

// sets |cur_cmd|, |cur_chr|, |cur_tok|, and expands macros
void get_x_token();

// |get_x_token| without the initial |get_next|
void x_token();

// invokes a user-defined control sequence
void macro_call();

// reads a mandatory |LEFT_BRACE|
void scan_left_brace();

void scan_optional_equals();

// look for a given string
bool scan_keyword(char *s);

// fetch an internal parameter
void scan_something_internal(small_number level, bool negative);

void scan_eight_bit_int();

void scan_char_num();

void scan_four_bit_int();

void scan_fifteen_bit_int();

void scan_twenty_seven_bit_int();

// sets |cur_val| to an integer
void scan_int();

// sets |cur_val| to a dimension
void scan_dimen(bool mu, bool inf, bool shortcut);

// sets |cur_val| to a glue spec pointer
void scan_glue(small_number level);

pointer scan_rule_spec();

pointer the_toks();

void ins_the_toks();

void conv_toks();

pointer scan_toks(bool macro_def, bool xpand);

void read_toks(int n, pointer r);

void pass_text();

void conditional();

void begin_name();

bool more_name(ASCII_code c);

void end_name();

void pack_file_name(str_number n, str_number a, str_number e);

str_number make_name_string();

void scan_file_name();

void pack_job_name(str_number s);

void scan_font_ident();

// sets |cur_val| to |font_info| location
void find_font_dimen(bool writing);

// scans a box specification and left brace
void scan_spec(int c, bool three_codes);

#ifdef INIT
void new_patterns();
#endif

#endif
// ~~~ End section 1381 ~~~
