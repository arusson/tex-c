# Section 1257

> ![NOTE]
> String `"FONT"` must be added to the pool.

```c << Read the other strings >>+=
put_string("FONT"); // FONT_STRING: 269
```

```c << Internal strings numbers in the pool >>+=
#define FONT_STRING 269
```

```c << Declare subprocedures for |prefixed_command| >>+=
void new_font(small_number a) {
    pointer u;                   // user's font identifier
    scaled s;                    // stated "at" size, or negative of scaled magnification
    int f;                       // runs through existing fonts
    str_number t;                // name for the frozen font identifier
    int old_setting;             // holds |selector| setting
    str_number flushable_string; // string not yet referenced
    
    if (job_name == 0) {
        // avoid confusing `texput` with the font name
        open_log_file();
    }
    get_r_token();
    u = cur_cs;
    if (u >= HASH_BASE) {
        t = text(u);
    }
    else if (u >= SINGLE_BASE) {
        if (u == NULL_CS) {
            t = FONT_STRING; // "FONT"
        }
        else {
            t = u - SINGLE_BASE;
        }
    }
    else {
        old_setting = selector;
        selector = NEW_STRING;
        print("FONT");
        print_strnumber(u - ACTIVE_BASE);
        selector = old_setting;
        str_room(1);
        t = make_string();
    }
    define(u, SET_FONT, NULL_FONT);
    scan_optional_equals();
    scan_file_name();
    // << Scan the font size specification >>
    // << If this font has already been loaded, set |f| to the internal font number and |goto common_ending| >>
    f = read_font_info(u, cur_name, cur_area, s);
common_ending:
    equiv(u) = f;
    eqtb[FONT_ID_BASE + f] = eqtb[u];
    font_id_text(f) = t;
}
```
