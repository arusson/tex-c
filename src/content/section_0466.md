# Section 466

```c << Copy the token list >>=
p = TEMP_HEAD;
link(p) = null;
if (cur_val_level == IDENT_VAL) {
    store_new_token(CS_TOKEN_FLAG + cur_val);
}
else if (cur_val != null) {
    r = link(cur_val); // do not copy the reference count
    while (r != null) {
        fast_store_new_token(info(r));
        r = link(r);
    }
}
return p;
```
