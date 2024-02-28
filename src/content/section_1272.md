# Section 1272

Files for `\read` are opened and closed by the *IN_STREAM* command.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("openin", IN_STREAM, 1);
primitive("closein", IN_STREAM, 0);
```
