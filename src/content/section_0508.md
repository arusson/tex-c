# Section 508

Note also that '`\ifx`' decides that macros `\a` and `\b` are different in examples like this:

<div align="center">

`\def\a{\c}` $\qquad$ `\def\c{}`<br>
`\def\b{\d}` $\qquad$ `\def\d{}`
</div>

```c << Test if two macro texts match >>=
p = link(cur_chr);
q = link(equiv(n)); // omit reference counts
if (p == q) {
    b = true;
}
else {
    while (p != null && q != null) {
        if (info(p) != info(q)) {
            p = null;
        }
        else {
            p = link(p);
            q = link(q);
        }
    }
    b = (p == null && q == null);
}
```
