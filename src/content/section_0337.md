# Section 337

An outer control sequence that occurs in a `\read` will not be reread, since the error recovery for `\read` is not very powerful.

```c << Back up an outer control sequence so that it can be reread >>=
if (cur_cs != 0) {
    if (state == TOKEN_LIST || name < 1 || name > 17) {
        p = get_avail();
        info(p) = CS_TOKEN_FLAG + cur_cs;
        back_list(p); // prepare to read the control sequence again
    }
    cur_cmd = SPACER;
    cur_chr = ' '; // replace it by a space
}
```
