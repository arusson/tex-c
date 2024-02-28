# Section 1289

When the case of a *chr_code* changes, we don't change the *cmd*.
We also change active characters, using the fact that *CS_TOKEN_FLAG + ACTIVE_BASE* is a multiple of&nbsp;256.

```c << Change the case of the token in |p|, if a change is appropriate >>=
t = info(p);
if (t < CS_TOKEN_FLAG + SINGLE_BASE) {
    c = t % 256;
    if (equiv(b + c) != 0) {
        info(p) = t - c + equiv(b + c);
    }
}
```
