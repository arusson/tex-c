# Section 1052

Either `\dump` or `\end` will cause *main_control* to enter the endgame, since both of them have *'STOP'* as their command code.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("end", STOP, 0);
primitive("dump", STOP, 1);
```
