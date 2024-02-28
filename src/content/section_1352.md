# Section 1352

When '`\write 12{...}`' appears, we scan the token list '`{...}`' without expanding its macros; the macros will be expanded later when this token list is rescanned.

```c << Implement \write >>=
k = cur_cs;
new_write_whatsit(WRITE_NODE_SIZE);
cur_cs = k;
p = scan_toks(false, false);
write_tokens(tail) = def_ref;
```
