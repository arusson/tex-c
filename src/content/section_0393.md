# Section 393

```c << Store the current token, but |goto continue_lbl| if it is a blank space that would become an undelimited parameter >>=
if (cur_tok == SPACE_TOKEN
    && info(r) <= END_MATCH_TOKEN
    && info(r) >= MATCH_TOKEN)
{
    goto continue_lbl;
}
store_new_token(cur_tok);
```
