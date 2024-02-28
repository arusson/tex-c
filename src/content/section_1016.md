# Section 1016

```c << Update the values of |first_mark| and |bot_mark| >>=
if (first_mark == null) {
    first_mark = mark_ptr(p);
    add_token_ref(first_mark);
}
if (bot_mark != null) {
    delete_token_ref(bot_mark);
}
bot_mark = mark_ptr(p);
add_token_ref(bot_mark);
```
