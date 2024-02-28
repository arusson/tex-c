# Section 710

When the following code is executed, *char_tag(q)* will be equal to *EXT_TAG* if and only if a built-up symbol is supposed to be returned.

```c << Make variable |b| point to a box for |(f, c)| >>=
if (char_tag(q) == EXT_TAG) {
    // << Construct an extensible character in a new box |b|, using recipe |rem_byte(q)| and font |f| >>
}
else {
    b = char_box(f, c);
}
```
