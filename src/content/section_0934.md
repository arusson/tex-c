# Section 934

We have now completed the hyphenation routine, so the *line_break* procedure is finished at last.
Since the hyphenation exception table is fresh in our minds, it's a good time to deal with the routine that adds new entries to it.

When $\TeX$ has scanned '`\hyphenation`', it calls on a procedure named *new_hyph_exceptions* to do the right thing.

```c include/parser.h
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
```

```c parser/hyph_scan.c
// << Start file |hyph_scan.c| >>

// enters new exceptions
void new_hyph_exceptions() {
    int n;             // length of current word; not always a |small_number|
    int j;             // an index into |hc|
    int h;             // an index into |hyph_word| and |hyph_list|
    str_number k;      // an index into |str_start|
    pointer p;         // head of a list of hyphen positions
    pointer q;         // used when creating a new node for list |p|
    str_number s, t;   // strings being compared or stored
    pool_pointer u, v; // indices into |str_pool|
    
    scan_left_brace(); // a left brace must follow \\hyphenation}
    set_cur_lang;
    // << Enter as many hyphenation exceptions as are listed, until coming to a right brace; then |return| >>
}
```
