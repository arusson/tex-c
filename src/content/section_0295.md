# Section 295

Here's the way we sometimes want to display a token list, given a pointer to its reference count; the pointer may be null.

```c io/display_tokens.c
void token_show(pointer p) {
    if (p != null) {
        show_token_list(link(p), null, 10000000);
    }
}
```
