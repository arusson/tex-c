# Section 356

```c << Scan ahead in the buffer until finding a nonletter; if an expanded code is encountered, reduce it and |goto start_cs|; otherwise if a multiletter control sequence is found, adjust |cur_cs| and |loc|, and |goto found| >>=
do {
    cur_chr = buffer[k];
    cat = cat_code(cur_chr);
    incr(k);
} while (cat == LETTER && k <= limit);
// << If an expanded code is present, reduce it and |goto start_cs| >>
if (cat != LETTER) {
    decr(k);
} // now |k| points to first nonletter
if (k > loc + 1) {
    // multiletter control sequence has been scanned
    cur_cs = id_lookup(loc, k - loc);
    loc = k;
    goto found;
}
```
