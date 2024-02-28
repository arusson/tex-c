# Section 1284

The *error* routine calls on *give_err_help* if help is requested from the *err_help* parameter.

```c error.c
void give_err_help() {
    token_show(err_help);
}
```
