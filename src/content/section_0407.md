# Section 407

In case you are getting bored, here is a slightly less trivial routine:
Given a string of lowercase letters, like '`pt`' or '`plus`' or '`width`', the *scan_keyword* routine checks to see whether the next tokens of input match this string.
The match must be exact, except that uppercase letters will match their lowercase counterparts; uppercase equivalents are determined by subtracting `'a'` − `'A'`, rather than using the *uc_code* table, since $\TeX$ uses this routine only for its own limited set of keywords.

If a match is found, the characters are effectively removed from the input and *true* is returned.
Otherwise *false* is returned, and the input is left essentially unchanged (except for the fact that some macros may have been expanded, etc.).

```c parser/subroutines.c
// look for a given string
bool scan_keyword(char *s) {
    pointer p; // tail of the backup list
    pointer q; // new node being added to the token list via |store_new_token|
    int k; // index into the string |s|
    int len = strlen(s);
    p = BACKUP_HEAD;
    link(p) = null;
    k = 0;
    while (k < len) {
        get_x_token(); // recursion is possible here
        if (cur_cs == 0
            && (cur_chr == s[k] || cur_chr == s[k] - 'a' + 'A'))
        {
            store_new_token(cur_tok);
            incr(k);
        }
        else if (cur_cmd != SPACER || p != BACKUP_HEAD) {
            back_input();
            if (p != BACKUP_HEAD) {
                back_list(link(BACKUP_HEAD));
            }
            return false;
        }
    }
    flush_list(link(BACKUP_HEAD));
    return true;
}
```
