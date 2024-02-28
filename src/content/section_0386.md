# Section 386

The following code is activated when *cur_cmd = TOP_BOT_MARK* and when *cur_chr* is a code like *TOP_MARK_CODE*.

```c << Insert the appropriate mark text into the scanner >>=
if (cur_mark[cur_chr] != null) {
    begin_token_list(cur_mark[cur_chr], MARK_TEXT);
}
```
