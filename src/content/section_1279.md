# Section 1279

```c builder/independent.c
void issue_message() {
    int old_setting; // holds |selector| setting
    int c;           // identifies \message and \errmessage
    str_number s;    // the message
    
    c = cur_chr;
    link(GARBAGE) = scan_toks(false, true);
    old_setting = selector;
    selector = NEW_STRING;
    token_show(def_ref);
    selector = old_setting;
    flush_list(def_ref);
    str_room(1);
    s = make_string();
    if (c == 0) {
        // << Print string |s| on the terminal >>
    }
    else {
        // << Print string |s| as an error message >>
    }
    flush_string;
}
```
