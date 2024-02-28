# Section 319

```c << Pseudoprint the token list >>=
begin_pseudoprint;
if (token_type < MACRO) {
    show_token_list(start, loc, 100000);
}
else {
    show_token_list(link(start), loc, 100000); // avoid reference count
}
```
