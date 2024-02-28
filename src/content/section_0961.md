# Section 961

Novices are not supposed to be using `\patterns`, so the error messages are terse.
(Note that all error messages appear in $\TeX$'s string pool, even if they are used only by `INITEX`.)

```c << Enter all of the patterns into a linked trie, until coming to a right brace >>=
k = 0;
hyf[0] = 0;
digit_sensed = false;
while(true) {
    get_x_token();
    switch (cur_cmd) {
    case LETTER:
    case OTHER_CHAR:
        // << Append a new letter or a hyphen level >>
        break;
    
    case SPACER:
    case RIGHT_BRACE:
        if (k > 0) {
            // << Insert a new pattern into the linked trie >>
        }
        if (cur_cmd == RIGHT_BRACE) {
            goto done;
        }
        k = 0;
        hyf[0] = 0;
        digit_sensed = false;
        break;
  
    default:
        print_err("Bad ");
        print_esc("patterns");
        help1("(See Appendix H.)");
        error();
    }
}
done:
```
