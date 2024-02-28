# Section 1327

```c << Undump a couple more things and the closing check word >>=
undump(BATCH_MODE, ERROR_STOP_MODE, interaction);
undump(0, str_ptr, format_ident);
undump_int(x);
if (x != 69069) {
    goto bad_fmt;
}
```
