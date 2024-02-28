# Section 1356

```c << Display the whatsit node |p| >>=
switch (subtype(p)) {
case OPEN_NODE:
    print_write_whatsit("openout", p);
    print_char('=');
    print_file_name(open_name(p), open_area(p), open_ext(p));
    break;

case WRITE_NODE:
    print_write_whatsit("write", p);
    print_mark(write_tokens(p));
    break;

case CLOSE_NODE:
    print_write_whatsit("closeout", p);
    break;

case SPECIAL_NODE:
    print_esc("special");
    print_mark(write_tokens(p));
    break;

case LANGUAGE_NODE:
    print_esc("setlanguage");
    print_int(what_lang(p));
    print(" (hyphenmin ");
    print_int(what_lhm(p));
    print_char(',');
    print_int(what_rhm(p));
    print_char(')');
    break;

default:
    print("whatsit?");
}
```
