# Section 1219

Both `\let` and `\futurelet` share the command code *LET*.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("let", LET, NORMAL);
primitive("futurelet", LET, NORMAL + 1);
```
