# Section 406

```c << Get the next non-blank non-call token >>=
do {
    get_x_token();
} while (cur_cmd == SPACER);
```
