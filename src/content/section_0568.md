# Section 568

Only the first two words of the header are needed by $\TeX82$.

```c << Read the TFM header >>=
if (lh < 2) {
    abort;
}
store_four_quarters(font_check[f]);
read_sixteen(z); // this rejects a negative design size
fget(temp);
z = z*256 + temp;
fget(temp);
z = z*16 + (temp / 16);
if (z < UNITY) {
    abort;
}
while (lh > 2) {
    fget(temp);
    fget(temp);
    fget(temp);
    fget(temp);
    decr(lh); // ignore the rest of the header
}
font_dsize[f] = z;
if (s != -1000) {
  if (s >= 0) {
    z = s;
  }
  else {
    z = xn_over_d(z, -s, 1000);
  }
}
font_size[f] = z;
```
