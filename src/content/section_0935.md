# Section 935

```c << Enter as many hyphenation exceptions as are listed, until coming to a right brace; then |return| >>=
n = 0;
p = null;
while(true) {
    get_x_token();
reswitch:
    switch (cur_cmd) {
    case LETTER:
    case OTHER_CHAR:
    case CHAR_GIVEN:
        // << Append a new letter or hyphen >>
        break;
    
    case CHAR_NUM:
        scan_char_num();
        cur_chr = cur_val;
        cur_cmd = CHAR_GIVEN;
        goto reswitch;
    
    case SPACER:
    case RIGHT_BRACE:
        if (n > 1) {
            // << Enter a hyphenation exception >>
        }
        if (cur_cmd == RIGHT_BRACE) {
            return;
        }
        n = 0;
        p = null;
        break;
    
    default:
        // << Give improper \hyphenation error >>
    }
}
```
