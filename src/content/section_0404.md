# Section 404

```c << Get the next non-blank non-relax non-call token >>=
do {
    get_x_token();
} while (cur_cmd == SPACER || cur_cmd == RELAX);
```
