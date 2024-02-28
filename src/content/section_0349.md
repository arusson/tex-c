# Section 349

The following code is performed only when *cur_cmd = SPACER*.

```c << Enter |SKIP_BLANKS| state, emit a space >>=
state = SKIP_BLANKS;
cur_chr = ' ';
```
