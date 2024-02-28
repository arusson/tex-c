# Section 1371

The final line of this routine is slightly subtle; at least, the author didn't think about it until getting burnt! There is a used-up token list on the stack, namely the one that contained *END_WRITE_TOKEN*.
(We insert this artificial '`\endwrite`' to prevent runaways, as explained above.)
If it were not removed, and if there were numerous writes on a single page, the stack would overflow.

```c include/constants.h
#define END_WRITE_TOKEN (CS_TOKEN_FLAG + END_WRITE)
```

```c << Expand macros in the token list and make |link(def_ref)| point to the result >>=
q = get_avail();
info(q) = RIGHT_BRACE_TOKEN + '}';
r = get_avail();
link(q) = r;
info(r) = END_WRITE_TOKEN;
ins_list(q);
begin_token_list(write_tokens(p), WRITE_TEXT);
q = get_avail();
info(q) = LEFT_BRACE_TOKEN + '{';
ins_list(q);
// now we're ready to scan '{<token list>} \endwrite'
old_mode = mode;
mode = 0; // disable \prevdepth, \spacefactor, \lastskip, \prevgraf
cur_cs = write_loc;
q = scan_toks(false, true); // expand macros, etc.
get_token();
if (cur_tok != END_WRITE_TOKEN) {
    // << Recover from an unbalanced write command >>
}
mode = old_mode;
end_token_list(); // conserve stack space
```
