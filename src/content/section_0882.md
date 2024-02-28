# Section 882

```c << Change discretionary to compulsory and set |disc_break = true| >>=
t = replace_count(q);
// << Destroy the |t| nodes following |q|, and make |r| point to the following node >>
if (post_break(q) != null) {
    // << Transplant the post-break list >>
}
if (pre_break(q) != null) {
    // << Transplant the pre-break list >>
}
link(q) = r;
disc_break = true;
```
