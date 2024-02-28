# Section 458

The necessary conversion factors can all be specified exactly as fractions whose numerator and denominator sum to 32768 or less.
According to the definitions here, 2660&nbsp;dd $\approx$ 1000.33297&nbsp;mm;
this agrees well with the value 1000.333&nbsp;mm cited by Bosshard in *Technische Grundlagen zur Satzherstellung* (Bern, 1980).

```c include/parser.h
#define set_conversion(X, Y) num = (X); denom = (Y)
```

```c << Scan for all other units and adjust |cur_val| and |f| accordingly; |goto done| in the case of scaled points >>=
if (scan_keyword("in")) {
    set_conversion(7227, 100);
}
else if (scan_keyword("pc")) {
    set_conversion(12, 1);
}
else if (scan_keyword("cm")) {
    set_conversion(7227, 254);
}
else if (scan_keyword("mm")) {
    set_conversion(7227, 2540);
}
else if (scan_keyword("bp")) {
    set_conversion(7227, 7200);
}
else if (scan_keyword("dd")) {
    set_conversion(1238, 1157);
}
else if (scan_keyword("cc")) {
    set_conversion(14856, 1157);
}
else if (scan_keyword("sp")) {
    goto done;
}
else {
    // << Complain about unknown unit and |goto done2| >>
}
cur_val = xn_over_d(cur_val, num, denom);
f = (num * f + 0x10000 * remainder_) / denom;
cur_val += f / 0x10000;
f %= 0x10000;
done2:
```
