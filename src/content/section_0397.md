# Section 397

When the following code becomes active, we have matched tokens from *s* to the predecessor of *r*, and we have found that *cur_tok* $\ne$ *info(r)*.
An interesting situation now presents itself:
If the parameter is to be delimited by a string such as '`ab`', and if we have scanned '`aa`', we want to contribute one '`a`' to the current parameter and resume looking for a '`b`'.
The program must account for such partial matches and for others that can be quite complex.
But most of the time we have *s = r* and nothing needs to be done.

Incidentally, it is possible for `\par` tokens to sneak in to certain parameters of non-`\long` macros.
For example, consider a case like '`\def\a#1\par!{...}`' where the first `\par` is not followed by an exclamation point.
In such situations it does not seem appropriate to prohibit the `\par`, so $\TeX$ keeps quiet about this bending of the rules.

```c << Contribute the recently matched tokens to the current parameter, and |goto continue| if a partial match is still in effect; but abort if |s = null| >>=
if (s != r) {
    if (s == null) {
        // << Report an improper use of the macro and abort >>
    }
    else {
        t = s;
        do {
            store_new_token(info(t));
            incr(m);
            u = link(t);
            v = s;
            while(true) {
                if (u == r) {
                    if (cur_tok != info(v)) {
                        goto done;
                    }
                    else {
                        r = link(v);
                        goto continue_lbl;
                    }
                }
                if (info(u) != info(v)) {
                    goto done;
                }
                u = link(u);
                v = link(v);
            }
done:
            t = link(t);
        } while (t != r);
        r = s; // at this point, no tokens are recently matched
    }
}
```
