# Section 1114

Discretionary nodes are easy in the common case '`\-`', but in the general case we must process three braces full of items.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("-", DISCRETIONARY, 1);
primitive("discretionary", DISCRETIONARY, 0);
```
