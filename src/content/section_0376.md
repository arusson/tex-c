# Section 376

The processing of `\input` involves the *start_input* subroutine, which will be declared later; the processing of `\endinput` is trivial.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("input", INPUT, 0);
primitive("endinput", INPUT, 1);
```
