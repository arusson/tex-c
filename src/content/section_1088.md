# Section 1088

A paragraph begins when horizontal-mode material occurs in vertical mode, or when the paragraph is explicitly started by '`\indent`' or '`\noindent`'.

```c << Put each of TeX's primitives into the hash table >>+=
primitive("indent", START_PAR, 1);
primitive("noindent", START_PAR, 0);
```
