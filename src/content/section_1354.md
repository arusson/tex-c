# Section 1354

When '`\special{...}`' appears, we expand the macros in the token list as in `\xdef` and `\mark`.

```c << Implement \special >>=
new_whatsit(SPECIAL_NODE, WRITE_NODE_SIZE);
write_stream(tail) = null;
p = scan_toks(false, true);
write_tokens(tail) = def_ref;
```
