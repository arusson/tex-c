# Section 326

```c << Insert token |p| into TeX's input>>=
t = cur_tok;
cur_tok = p;
back_input();
cur_tok = t;
```
