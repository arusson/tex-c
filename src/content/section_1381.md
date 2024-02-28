# Section 1381

We specify here the safeguards on header files, includes and prototypes of functions.
Also, we need to add `#endif` to each header file to close the include safeguards.

---

```c << Start file |alignment.h| >>=
#ifndef ALIGNMENT_H_
#define ALIGNMENT_H_

#include "datastructures.h"
```

```c include/alignment.h
void init_align();

void align_peek();

void init_row();

void init_span(pointer p);

void init_col();

bool fin_col();

void fin_row();

void fin_align();
#endif
```

---

```c << Start file |arithmetic.h| >>=
#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include "tex.h"
```

```c include/arithmetic.h
int half(int x);

// converts a decimal fraction
scaled round_decimals(small_number k);

scaled mult_and_add(int n, scaled x, scaled y, scaled max_answer);

scaled x_over_n(scaled x, int n);

scaled xn_over_d(scaled x, int n, int d);

// compute badness, given |t >= 0|
halfword badness(scaled t, scaled s);
#endif
```

---

```c << Start file |breaker.h| >>=
#ifndef BREAKER_H_
#define BREAKER_H_

#include "datastructures.h"
```

```c include/breaker.h
void line_break(int final_widow_penalty);

void hyphenate();

void init_trie();

// adjust top after page break
pointer prune_page_top(pointer p);

// finds optimum page break
pointer vert_break(pointer p, scaled h, scaled d);

// extracts a page of height |h| from box |n|
pointer vsplit(eight_bits n, scaled h);

#endif
```

---

```c << Start file |builder.h| >>=
#ifndef BUILDER_H_
#define BUILDER_H_

#include "datastructures.h"
```

```c include/builder.h
pointer hpack(pointer p, scaled w, small_number m);

pointer vpackage(pointer p, scaled h, small_number m, scaled l);

void append_to_vlist(pointer b);

void box_error(eight_bits n);

void build_page();

void main_control();

void you_cant();

void report_illegal_case();

void append_glue();

void append_kern();

void off_save();

void handle_right_brace();

void extra_right_brace();

void normal_paragraph();

void begin_box(int box_context);

// the next input should specify a box or perhaps a rule
void scan_box(int box_context);

void package(small_number c);

small_number norm_min(int h);
void new_graf(bool indented);

void indent_in_hmode();

void head_for_vmode();

void end_graf();

void begin_insert_or_adjust();

void make_mark();

void append_penalty();

void delete_last();

void unpackage();

void append_italic_correction();

void append_discretionary();

void build_discretionary();

void make_accent();

void align_error();

void do_endv();

void prefixed_command();

void do_assignments();

void open_or_close_in();

void issue_message();

void shift_case();
#endif
```

---

```c << Start file |conditional.h| >>=
#ifndef CONDITIONAL_H_
#define CONDITIONAL_H_

#include "tex.h"
```

```c include/conditional.h
#endif
```

---

```c << Start file |constants.h| >>=
#ifndef CONSTANTS_H_
#define CONSTANTS_H_
```

```c include/constants.h
#endif
```

---

```c << Start file |datastructures.h| >>=
#ifndef DATASTRUCTURES_H_
#define DATASTRUCTURES_H_

#include "tex.h"
```

```c include/datastructures.h
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
```

---

```c << Start file |dvi.h| >>=
#ifndef DVI_H_
#define DVI_H_

#include "io.h"
#include "parser.h"
```

```c include/dvi.h
void write_dvi(int a, int b);

void dvi_swap();

void dvi_four(int x);

void dvi_font_def(internal_font_number f);

void movement(scaled w, eight_bits o);

void vlist_out();

// output the box |p|
void ship_out(pointer p);

void out_what(pointer p);
#endif
```

---

```c << Start file |texerror.h| >>=
#ifndef ERROR_H_
#define ERROR_H_

#include "io.h"
```

```c include/texerror.h
void error();

void int_error(int n);

void normalize_selector();

void succumb();
// prints |s| and that's it
void fatal_error(char *s);

// stop due to finiteness
void overflow(char *s, int n);

// consistency check violated; |s| tells where
void confusion(char *s);

void pause_for_instructions();

void mu_error();

void give_err_help();

void clear_for_error_prompt();
#endif
```

---

```c << Start file |extensions.h| >>=
#ifndef EXTENSIONS_H_
#define EXTENSIONS_H_

#include "datastructures.h"
```

```c include/extensions.h
void do_extension();

void new_whatsit(small_number s, small_number w);
#endif
```

---

```c << Start file |font_metric.h| >>=
#ifndef FONT_METRIC_H_
#define FONT_METRIC_H_

#include "datastructures.h"
#include "texerror.h"
```

```c include/font_metric.h
// input a `TFM` file
internal_font_number read_font_info(pointer u, str_number nom, str_number aire, scaled s);

void char_warning(internal_font_number f, eight_bits c);

pointer new_character(internal_font_number f, eight_bits c);

#endif
```

---

```c << Start file |io.h| >>=
#ifndef IO_H_
#define IO_H_

#include "strings.h"
```

```c include/io.h
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
```

---

```c << Start file |texmath.h| >>=
#ifndef MATH_H_
#define MATH_H_

#include "datastructures.h"
```

```c include/texmath.h
pointer new_noad();

// create a style node
pointer new_style(small_number s);

// create a choice node
pointer new_choice();

// construct the bar for a fraction
pointer fraction_rule(scaled t);

pointer overbar(pointer b, scaled k, scaled t);

pointer var_delimiter(pointer d, small_number s, scaled v);

pointer char_box(internal_font_number f, quarterword c);

pointer rebox(pointer b, scaled w);

pointer math_glue(pointer g, scaled m);

void math_kern(pointer p, scaled m);

void flush_math();

void mlist_to_hlist();

void init_math();

void start_eq_no();

void scan_math(pointer p);

void set_math_char(int c);

void math_limit_switch();

void math_radical();

void math_ac();

void append_choices();

void build_choices();

void sub_sup();

void math_fraction();

pointer fin_mlist(pointer p);

void math_left_right();

void after_math();

void resume_after_display();
#endif
```

---

```c << Start file |parser.h| >>=
#ifndef PARSER_H_
#define PARSER_H_

#include "datastructures.h"
```

```c include/parser.h
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
```

---

```c << Start file |strings.h| >>=
#ifndef STRINGS_H_
#define STRINGS_H_

#include "tex.h"
```

```c include/strings.h
// current string enters the pool
str_number make_string();

// test equality of strings
int str_eq_buf(str_number s, int k);

// test equality of strings
int str_eq_str(str_number s, str_number t);

#ifdef INIT
// initializes the string pool
void get_strings_started();
#endif

str_number put_string(char *s);

#endif
```

---

```c << Start file |tex.h| >>=
#ifndef TEX_H_
#define TEX_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "constants.h"
```

```c include/tex.h
void initialize();

// gets the terminal input started
bool init_terminal(int argc, char *argv[]);

void fix_date_and_time();

void close_files_and_terminate();

void final_cleanup();

#ifdef INIT
// initialize all the primitives
void init_prim();
#endif

#ifdef DEBUG
void debug_help();
#endif

#endif
```
