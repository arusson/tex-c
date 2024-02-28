// ~~~ Section 34 ~~~
// ~~~ Start file |io.h|, 1381 ~~~
#ifndef IO_H_
#define IO_H_

#include "strings.h"
// ~~~ End section 1381 ~~~

#define update_terminal fflush(stdout)
#define clear_terminal do_nothing
// ~~~ End section 34 ~~~

// ~~~ Section 36 ~~~
#define loc cur_input.loc_field // location of first unread character in buffer
// ~~~ End section 36 ~~~

// ~~~ Section 56 ~~~
#define wterm(X, ...)       printf(X, ##__VA_ARGS__)
#define wterm_char(X)       printf("%c", (X))
#define wterm_ln(X, ...)    printf(X"\n", ##__VA_ARGS__)
#define wterm_cr            printf("\n")
#define wlog(X, ...)        fprintf(log_file, X, ##__VA_ARGS__)
#define wlog_char(X)        fprintf(log_file, "%c", (X))
#define wlog_ln(X, ...)     fprintf(log_file, X"\n", ##__VA_ARGS__)
#define wlog_cr             fprintf(log_file, "\n")

#define write_ln(F, X, ...) fprintf((F), X"\n", ##__VA_ARGS__)
#define write_char(F, X)    fprintf((F), "%c", (X))
#define write_byte(F, X)    fputc((X), (F))
// ~~~ End section 56 ~~~

// ~~~ Section 71 ~~~
// prints a string and gets a line of input
#define prompt_input(X) print((X)); term_input()
// ~~~ End section 71 ~~~

// ~~~ Section 180 ~~~
// |str_room| need not be checked; see |show_box| below
#define node_list_display(X) append_char('.'); show_node_list((X)); flush_char
// ~~~ End section 180 ~~~

// ~~~ Section 298 ~~~
#define chr_cmd(X) print((X)); print_strnumber(chr_code)
// ~~~ End section 298 ~~~

// ~~~ Section 316 ~~~
#define begin_pseudoprint  \
    l = tally;             \
    tally = 0;             \
    selector = PSEUDO;     \
    trick_count = 1000000

#define set_trick_count                                         \
    do {                                                        \
        first_count = tally;                                    \
        trick_count = tally + 1 + ERROR_LINE - HALF_ERROR_LINE; \
        if (trick_count < ERROR_LINE) {                         \
            trick_count = ERROR_LINE;                           \
        }                                                       \
    } while (0)
// ~~~ End section 316 ~~~

// ~~~ Section 985 ~~~
#define print_plus(X, Y)                    \
    do {                                    \
        if (page_so_far[(X)] != 0) {        \
            print(" plus ");                \
            print_scaled(page_so_far[(X)]); \
            print((Y));                     \
        }                                   \
    } while (0)
// ~~~ End section 985 ~~~

// ~~~ Section 1303 ~~~
#define too_small(X)                            \
    printf("---! Must increase the %s\n", (X)); \
    goto bad_fmt
// ~~~ End section 1303 ~~~

// ~~~ Section 1305 ~~~
#define dump_wd(X)  fwrite(&X, 8, 1, fmt_file)
#define dump_int(X) putw((X), fmt_file)
#define dump_hh     dump_wd
#define dump_qqqq   dump_wd
// ~~~ End section 1305 ~~~

// ~~~ Section 1306 ~~~
#define undump_wd(X)  fread(&X, 8, 1, fmt_file)
#define undump_int(X) fread(&X, 4, 1, fmt_file)
#define undump_hh     undump_wd
#define undump_qqqq   undump_wd

#define undump(A, B, X)       \
    undump_int(x);            \
    if (x < (A) || x > (B)) { \
        goto bad_fmt;         \
    }                         \
    (X) = x

#define undump_size(A, B, S, X) \
    undump_int(x);              \
    if (x < (A)) {              \
        goto bad_fmt;           \
    }                           \
    if (x > (B)) {              \
        too_small(S);           \
    }                           \
    (X) = x
// ~~~ End section 1306 ~~~

// ~~~ Section 1309 ~~~
#define dump_four_ASCII           \
    qqqq_b0(w) = str_pool[k];     \
    qqqq_b1(w) = str_pool[k + 1]; \
    qqqq_b2(w) = str_pool[k + 2]; \
    qqqq_b3(w) = str_pool[k + 3]; \
    dump_qqqq(w)
// ~~~ End section 1309 ~~~

// ~~~ Section 1310 ~~~
#define undump_four_ASCII         \
    undump_qqqq(w);               \
    str_pool[k] = qqqq_b0(w);     \
    str_pool[k + 1] = qqqq_b1(w); \
    str_pool[k + 2] = qqqq_b2(w); \
    str_pool[k + 3] = qqqq_b3(w)
// ~~~ End section 1310 ~~~

// ~~~ Section 1381 ~~~
// open a text file for input
int a_open_in(alpha_file *f);

// open a text file for output
int a_open_out(alpha_file *f);

// open a binary file for input
int b_open_in(byte_file *f);

// open a binary file for output
int b_open_out(byte_file *f);

// open a word file for input
int w_open_in(word_file *f);

// open a word file for output
int w_open_out(word_file *f);

// close a text file
void a_close(alpha_file f);

// close a binary file
void b_close(byte_file f);

// close a word file
void w_close(word_file f);

// inputs the next line or returns |false|
int input_ln(alpha_file f);

// prints an end-of-line
void print_ln();

// prints a single character
void print_char(ASCII_code s);

// prints string s
void print(char *s);
void print_strnumber(int s);

// prints string s
void slow_print(int s);

// prints string |s| at beginning of line
void print_nl(char *s);
void print_nl_strnumber(str_number s);

// prints escape character, then |s|
void print_esc(char *s);
void print_esc_strnumber(str_number s);

// prints an integer in decimal form
void print_int(int n);

// prints two least significant digits
void print_two(int n);

// prints a positive integer in hexadecimal form
void print_hex(int n);

void print_roman_int(int n);

// prints a yet-unmade string
void print_current_string();

// gets a line from the terminal
void term_input();

// prints scaled real, rounded to five digits
void print_scaled(scaled s);

#ifdef DEBUG
// prints |w| in all ways
void print_word(memory_word w);
#endif

// prints highlights of list |p|
void short_display(int p);

// prints a glue specification
void print_spec(int p, char *s);

// prints a node list symbolically
void show_node_list(int p);

void show_box(pointer p);

// prints the mode represented by |m|
void print_mode(int m);

void print_skip_param(int n);

void print_param(int n);

// prepare to do some tracing
void begin_diagnostic();
void end_diagnostic(bool blank_line);

void print_length_param(int n);

#ifdef STAT
void show_eqtb(pointer n);
#endif

// prints a purported control sequence
void print_cs(int p);

// prints a purported control sequence
void sprint_cs(pointer p);

void show_token_list(int p, int q, int l);

void token_show(pointer p);

void print_meaning();

void print_cmd_chr(quarterword cmd, halfword chr_code);

void show_cur_cmd_chr();

// prints where the scanner is
void show_context();

void print_file_name(int n, int a, int e);

bool open_fmt_file();

void prompt_file_name(char *s, str_number e);

void open_log_file();

// TeX will \input something
void start_input();

// prints family and character
void print_fam_and_char(pointer p);
// prints a delimiter as 24-bit hex value
void print_delimiter(pointer p);

// display a noad field
void print_subsidiary_data(pointer p, ASCII_code c);

// the reader will kindly forgive this
void show_info();

void print_style(int c);

void print_size(int s);

void print_totals();

void show_whatever();

#ifdef INIT
void store_fmt_file();
#endif

bool load_fmt_file();

void print_write_whatsit(char *s, pointer p);
#endif
// ~~~ End section 1381 ~~~
